#include "timeserver.h"
#include "util/configuration.h"

using namespace rtm::rpc;
using namespace rtm::time;
using namespace rtm::util;

int main() {
  InitializeNetworking();
  TrueTime::GET();
  PServer server;
  // TODO: configure from file
  server.serve(Conf::get_timeserver_port());
}
