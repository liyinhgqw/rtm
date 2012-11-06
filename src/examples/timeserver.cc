#include "timeserver.h"

using namespace rtm::rpc;
using namespace rtm::time;

int main() {
  InitializeNetworking();
  TrueTime::GET();
  PServer server;
  // TODO: configure from file
  server.serve(55000);
}
