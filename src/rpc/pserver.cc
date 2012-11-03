#include "pserver.h"
#include "value.h"
#include "exceptions.h"

namespace rtm {
namespace rpc {

std::string PServer::dispatch(util::StringPiece method, util::StringPiece args) {
  MethodFactory* method_factory = MethodFactory::GET();
  MethodBase *methodClazz = method_factory->get(method.AsString());
  Log_Debug("dispatch method: %s %s", method.AsString().c_str(), args.AsString().c_str());
  Message *request = methodClazz->new_request_msg();
  Message *response = methodClazz->new_response_msg();
  request->ParseFromString(args.AsString());
  ValueT<std::string> value;
  std::string buffer;
  Encoder enc(&buffer);
  try {
    methodClazz->run(request, response);
    std::string ret;
    response->SerializeToString(&ret);

    value.value = ret;
    value.write(&enc);
  } catch (rpc_exception &e) {
    e.error();

    value.status = kCallError;
    value.setError(std::string(e.what()));
    value.write(&enc);
  }

  delete request;
  delete response;

  return buffer;
}

MethodFactory* MethodFactory::GET() {
  static MethodFactory* r = NULL;
  if (!r) {
    r = new MethodFactory;
  }
  return r;
}

void MethodFactory::reg(std::string name, MethodBase *method) {
  methods_.insert(std::make_pair(name, method));
}

MethodBase* MethodFactory::get(std::string name) {
  MethodMap::iterator it = methods_.find(name);
  if (it != methods_.end()) {
    return it->second;
  } else {
    return NULL;
  }
}

}
}


