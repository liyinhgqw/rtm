#include "kvserver.h"

using namespace rtm::rpc;

int main() {
  InitializeNetworking();
  RPC_REG(get, Get);
  PServer server;
  server.serve(55000);
}
