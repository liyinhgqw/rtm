#include "clientproxy.h"
#include "rpc/pclient.h"
#include "time/truetime.h"
#include "util/configuration.h"
#include "util/threadpool.h"

namespace rtm {
namespace rpc {

class PClientProxy: public ClientProxy {
public:
  PClientProxy();
  virtual ~PClientProxy();
  virtual bool call(std::string, Message&, Message&);
private:
  ThreadPool threadpool_;
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
/*
  for (std::list<Client*>::iterator it = client_list_.begin();
      it != client_list_.end(); it++) {
    PClient* pclient_ptr = dynamic_cast<PClient*>(*it);
    if (false == pclient_ptr->call(method, request, response)) {
      ret = false;
      break;
    }
  }
*/

  std::pair<int,int> callback;
  for (std::list<Client*>::iterator it = client_list_.begin();
    it != client_list_.end(); it++) {
    PClient* pclient_ptr = dynamic_cast<PClient*>(*it);
    threadpool_.callbackAsync(boost::bind(&PClient::call, pclient_ptr, method, request, response), callback);
  }
  if (false == pclient_ptr->call(method, request, response)) {
    ret = false;
    break;
  }


  return ret;
}

} // namespace rpc
} // namespace rtm
