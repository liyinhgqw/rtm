#ifndef KVSERVER_H_
#define KVSERVER_H_

#include <string>
#include <fstream>
#include <iostream>

#include "rpc/pserver.h"
#include "time/truetime.h"
#include "kv.pb.h"

namespace rtm {
namespace rpc {

class Get: public MethodBase {
public:
  virtual Message* new_request_msg() {
    return new GetRequest;
  }
  virtual Message* new_response_msg() {
    return new GetResponse;
  }
  virtual void run(Message* request_, Message* response_) {
    GetRequest *request;
    GetResponse *response;
    request = dynamic_cast<GetRequest*>(request_);
    response = dynamic_cast<GetResponse*>(response_);
    std::string key = request->key();
    Log_Info("RUN: %s", key.c_str());
    std::string value = "hello " + key + " !";
    response->set_value(value);
  }
};

class Put: public MethodBase {
public:
  virtual Message* new_request_msg() {
    return new PutRequest;
  }
  virtual Message* new_response_msg() {
    return new PutResponse;
  }
  virtual void run(Message* request_, Message* response_) {
    PutRequest *request;
    PutResponse *response;
    request = dynamic_cast<PutRequest*>(request_);
    response = dynamic_cast<PutResponse*>(response_);
    std::string key = request->key();
    std::string value = request->value();
    Log_Info("RUN: %s %s", key.c_str(), value.c_str());

    response->set_ret(true);
    // write <key, value> to a file
    ofstream ofs;
    ofs.open("/tmp/rtm.db", ios::app);
    ofs << key << "\t" << value << std::endl;
    ofs.close();
  }
};

} // namespace rpc
} // namespace rtm
#endif /* KVSERVER_H_ */
