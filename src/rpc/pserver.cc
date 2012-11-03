#include "pserver.h"

namespace rtm {
namespace rpc {

std::string PServer::dispatch(util::StringPiece method, util::StringPiece args) {
  MethodFactory* method_factory = MethodFactory::GET();
  MethodBase *methodClazz = method_factory->get(method.AsString());
  Message *request = methodClazz->new_request_msg();
  Message *response = methodClazz->new_response_msg();
  request->ParseFromString(args.AsString());
  methodClazz->run(request, response);
  std::string ret;
  response->SerializeToString(&ret);
  delete request;
  delete response;

  return ret;
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


