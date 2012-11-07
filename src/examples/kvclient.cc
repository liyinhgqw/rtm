#include "examples/kvclient.h"
#include "rpc/pclient.h"
#include "rpc/clientproxy.h"
#include "time/truetime.h"
#include "kv.pb.h"

#include <iostream>

using namespace google::protobuf;
using namespace rtm::rpc;
using namespace rtm::time;

int main() {
  InitializeNetworking();
  InitializeTrueTime();


  GetRequest request;
  GetResponse response;
  request.set_key("mao");

  // TODO: void-request, void-response
  ClientProxy* cproxy = ClientProxy::create("rtm");
  if (!cproxy) Log_Fatal("Client proxy cannot be set up.");
  cproxy->call("get", request, response);
  std::cout << response.value() << std::endl;
}

