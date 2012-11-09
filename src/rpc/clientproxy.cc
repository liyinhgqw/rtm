#include "clientproxy.h"
#include "rpc/pclient.h"
#include "time/truetime.h"
#include "util/configuration.h"
#include "util/threadpool.h"

namespace rtm {
namespace rpc {

class PClientProxy : public ClientProxy {
public:
  PClientProxy();
  virtual ~PClientProxy();
  virtual bool call(std::string, Message&, Message&);
private:
  CallbackThreadPool threadpool_;
};

ClientProxy* ClientProxy::create(std::string protocol) {
  if (protocol == "rtm")
    return new PClientProxy();
  else
    return NULL;
}

PClientProxy::PClientProxy() {
  std::list<std::string> servers_addr = util::Conf::get_rtmserver_hostport();
  for (std::list<std::string>::iterator it = servers_addr.begin(); it
      != servers_addr.end(); it++) {
    PClient* pclient_ptr = new PClient(EndpointHelper::rtm(*it),
                                       rtm::util::StringPrintf("rtm"));
    client_list_.push_back(pclient_ptr);
  }
}

PClientProxy::~PClientProxy() {
  for (std::list<Client*>::iterator it = client_list_.begin(); it
      != client_list_.end(); it++) {
    delete (*it);
  }

}

// Strawman. TODO: async call, using multi-thread???
bool PClientProxy::call(std::string method, Message& request, Message& response) {
  bool ret = true;
  std::string request_str, response_str;
  std::list<Callback*> callback_list;
  for (std::list<Client*>::iterator it = client_list_.begin(); it
      != client_list_.end(); it++) {
    Callback* cb_ptr = new Callback;
    callback_list.push_back(cb_ptr);
    PClient* pclient_ptr = dynamic_cast<PClient*> (*it);

    request.SerializeToString(&request_str);
    threadpool_.runAsync(boost::bind(&PClient::raw_call, pclient_ptr, method,
                                     request_str, response_str), cb_ptr);
  }
  while (!callback_list.empty()) {
    Callback* cb = callback_list.front();
    if (cb->finished) {
      if (!cb->ret) {
        ret = false;
        break;
      }
      delete cb;
      callback_list.pop_front();
    } else {
      sleep(0.001);
    }
  }
  while (!callback_list.empty()) {
    Callback* cb = callback_list.front();
    delete cb;
    callback_list.pop_front();
  }

  if (ret)
    response.ParseFromString(response_str);

  return ret;
}

} // namespace rpc
} // namespace rtm
