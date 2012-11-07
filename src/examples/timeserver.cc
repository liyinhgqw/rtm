#include "timeserver.h"
#include "util/configuration.h"

using namespace rtm::rpc;
using namespace rtm::time;
using namespace rtm::util;

int main() {
  printf("timeserver port:");

  InitializeNetworking();
  TrueTime::GET();

  PServer server;
  // TODO: configure from file

  printf("%d \n", Conf::get_timeserver_port());
  server.serve(Conf::get_timeserver_port());

}
