#include "examples/kvclient.h"
#include "rpc/pclient.h"
#include "kv.pb.h"
#include <iostream>

using namespace google::protobuf;
using namespace rtm::rpc;

int main() {
  PClient client(EndpointHelper::rtm("127.0.0.1:55000"), rtm::util::StringPiece("rtm"));

  GetRequest request;
  GetResponse response;
  request.set_key("mao");

  client.call("get", request, response);
  std::cout << response.value() << std::endl;
}

