#include "examples/kvclient.h"
#include "rpc/pclient.h"
#include "time/truetime.h"
#include "kv.pb.h"

#include <iostream>

using namespace google::protobuf;
using namespace rtm::rpc;
using namespace rtm::time;

int main() {
  InitializeNetworking();
  InitializeTrueTime();
  PClient client(EndpointHelper::rtm("127.0.0.1:55000"), rtm::util::StringPiece("rtm"));

  GetRequest request;
  GetResponse response;
  request.set_key("mao");

  // TODO: void-request, void-response
  client.call("get", request, response);
  std::cout << response.value() << std::endl;
}

