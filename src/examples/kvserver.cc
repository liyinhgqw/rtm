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
  RPC_REG(put, Put);
  PServer server;
  server.serve(Conf::get_rtmserver_port());
}
