#ifndef RTM_CONNECTION_H_
#define RTM_CONNECTION_H_

#include <cinttypes>
#include <boost/unordered_map.hpp>
#include <string>

#include "rpc/socket.h"

#include "util/common.h"
#include "util/marshal.h"
#include "util/string.h"

namespace rtm {
namespace rpc {

class Future;
class Server;

struct Endpoint: public ::rtm::Serializable {
  std::string protocol;
  std::string host;
  int32_t port;
  std::string serviceType;

  // In lieu of adding pointer support to thrift, this is a terrible hack for
  // caching or referring to a local server instance.
  int64_t localServer;

  void write(::rtm::Encoder* e) const;
  void read(::rtm::Decoder* d);
};

struct RPCError: public ::rtm::Serializable {
  std::string msg;
  std::string hostname;
  double time;

  std::string filename;
  int lineNumber;

  RPCError();
  RPCError(const std::string& msg);

  void write(Encoder* e) const;
  void read(Decoder* d);

  static std::string traceAsString(const std::vector<RPCError>& trace);
};

struct EndpointHelper {
  static Endpoint local(const Server* s);
  static Endpoint rtm(const std::string& hostport);
};

class Connection {
public:
  static Connection* create(const Endpoint& url);

  virtual void send(Future* result, const util::StringPiece& method,
      const util::StringPiece& args) = 0;
  virtual void wait(Future* f) = 0;
};


} // namespace rpc
} // namespace rtm

#endif /* RTM_CONNECTION_H_ */
