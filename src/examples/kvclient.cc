#include "examples/kvclient.h"
#include "rpc/pclient.h"
#include "rpc/clientproxy.h"
#include "time/truetime.h"
#include "kv.pb.h"
#include "util/string.h"

#include <iostream>

using namespace google::protobuf;
using namespace rtm::rpc;
using namespace rtm::time;
using namespace rtm::util;

int main() {
  InitializeNetworking();
  InitializeTrueTime();
  /*
   GetRequest request;
   GetResponse response;
   request.set_key("mao");
   */

  ClientProxy* cproxy = ClientProxy::create("rtm");
  if (!cproxy) Log_Fatal("Client proxy cannot be set up.");

  PutRequest request;
  PutResponse response;

  for (int i = 0; i < 10000; i++) {
    std::string key, value;
    key = StringPrintf("%d", i);
    value = StringPrintf("%f", TrueTime::GET()->d_now());
    request.set_key(key);
    request.set_value(value);
    Log_Debug("put key %d", i);
    cproxy->call("put", request, response);
  }
  // TODO: void-request, void-response
  std::cout << response.ret() << std::endl;
}

