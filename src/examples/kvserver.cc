#include "kvserver.h"
#include "time/truetime.h"

using namespace rtm::rpc;
using namespace rtm::time;

int main() {
  InitializeNetworking();
  InitializeTrueTime();
  RPC_REG(get, Get);
  PServer server;
  server.serve(55000);
}
