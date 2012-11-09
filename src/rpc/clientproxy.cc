#include "clientproxy.h"
#include "rpc/pclient.h"
#include "time/truetime.h"
#include "util/configuration.h"
#include "util/threadpool.h"

#include <boost/shared_ptr.hpp>

namespace rtm {
namespace rpc {

class PClientProxy: public ClientProxy {
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
  for (std::list<std::string>::iterator it = servers_addr.begin();
      it != servers_addr.end(); it++) {
    PClient* pclient_ptr = new PClient(EndpointHelper::rtm(*it), rtm::util::StringPrintf("rtm"));
    client_list_.push_back(pclient_ptr);
  }
}

PClientProxy::~PClientProxy() {
  for (std::list<Client*>::iterator it = client_list_.begin();
      it != client_list_.end(); it++) {
    delete (*it);
  }

}

// Strawman. TODO: async call, using multi-thread???
bool PClientProxy::call(std::string method, Message& request, Message& response) {
  bool ret = true;
  std::list<boost::shared_ptr<Callback*> > callback_list;
  for (std::list<Client*>::iterator it = client_list_.begin();
    it != client_list_.end(); it++) {
    boost::shared_ptr<Callback*> cb_ptr(new Callback);
    callback_list.push_back(cb_ptr);
    PClient* pclient_ptr = dynamic_cast<PClient*>(*it);
    threadpool_.runAsync(boost::bind(&PClient::call, pclient_ptr, method, request, response), cb_ptr);
  }
  while (!callback_list.empty()) {
    Callback* cb = callback_list.front();
    if (cb->finished) {
      if (!cb->ret) {
        ret = false;
        break;
      }
      callback_list.pop_front();
    } else {
      sleep(0.001);
    }
  }

  return ret;
}

} // namespace rpc
} // namespace rtm
