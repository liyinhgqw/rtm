#ifndef PSERVER_H_
#define PSERVER_H_

#include "server.h"
#include <boost/unordered_map.hpp>
#include <google/protobuf/message.h>

namespace rtm {
namespace rpc {

using namespace google::protobuf;

class PServer: public Server {
public:
  virtual std::string dispatch(util::StringPiece method, util::StringPiece args);
};

// user implements MethodBase
class MethodBase {
public:
  virtual Message* new_request_msg() = 0;
  virtual Message* new_response_msg() = 0;
  virtual void run(Message*, Message*) = 0;
};

#define RPC_REG(name, clazz)\
MethodBase* name##_method_ptr = new (clazz)();\
MethodFactory::GET()->reg(#name, name##_method_ptr);

class MethodFactory {
public:
  typedef boost::unordered_map<std::string, MethodBase*> MethodMap;

  MethodFactory() {}
  static MethodFactory* GET();
  void reg(std::string name, MethodBase *method);
  MethodBase* get(std::string name);

private:
  MethodMap methods_;
};

} // namespace rpc
} // namespace rtm
#endif /* PSERVER_H_ */
