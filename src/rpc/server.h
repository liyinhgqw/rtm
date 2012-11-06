#ifndef RTM_SERVER_H_
#define RTM_SERVER_H_

#include <string>
#include <set>

#include "rpc/connection.h"
#include "rpc/future.h"
//#include "util/threadpool.h"
#include "util/string.h"
#include "time/timequeue.h"

namespace rtm {
namespace rpc {

class Client;
class ServerSocket;
class Socket;

class Server {
private:
  ServerSocket* serverSocket_;
  std::vector<Socket*> clients_;
//  ThreadPool dispatchPool_;
  time::TimeQueue dispatchQueue_;

  void doDispatch(Socket* client, RPCMessage* msg, bool outdated);
  void pushDispatch(Socket* client, RPCMessage* msg);

//  std::set<std::pair<Socket*, int64_t> > repeat_;
protected:
public:
  Server();
  void serve(int port);

  virtual std::string dispatch(util::StringPiece method, util::StringPiece args) = 0;
};

} // namespace rpc
} // namespace rtm

#endif /* RTM_SERVER_H_ */
