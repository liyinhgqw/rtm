#include "kvserver.h"
#include "util/xmlparser.h"
#include "util/configuration.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace rtm::rpc;
using namespace rtm::time;
using namespace rtm::util;

int main() {
  InitializeNetworking();
  InitializeTrueTime();
  RPC_REG(get, Get);
  PServer server;
  server.serve(Conf::get_rtmserver_port());
  std::list<std::string> servers_addr = Conf::get_rtmserver_hostport();
  for (std::list<std::string>::iterator it = servers_addr.begin();
      it != servers_addr.end(); it++) {
    std::cout << *it << std::endl;
  }
}
