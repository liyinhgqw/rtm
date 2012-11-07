#include "configuration.h"
#include "logging.h"
#include <stdlib.h>
#include <fstream>

namespace rtm {
namespace util {

const std::string Conf::conf_file = std::string(getenv("RTM_HOME"))+"/conf/rtm.xml";

int Conf::get_rtmserver_port() {
  return XmlParser::parse<int>(conf_file, "configuration.rtmserver.port");
}

int Conf::get_timeserver_port() {
  return XmlParser::parse<int>(conf_file, "configuration.timeserver.port");
}

std::string Conf::get_timeserver_host() {
  return XmlParser::parse(conf_file, "configuration.timeserver.host");
}

std::string Conf::get_timeserver_hostport() {
  return XmlParser::parse(conf_file, "configuration.timeserver.host") + ":"
          +  XmlParser::parse(conf_file, "configuration.timeserver.port");
}

std::list<std::string> Conf::get_rtmserver_hostport() {
  std::list<std::string> server_list;
  // parse $HOSTLIST(conf/servers)

  Log_Debug("hostlist: %s", getenv("HOSTLIST"));
  std::string hostlist(getenv("HOSTLIST"));

  std::ifstream fs;
  fs.open(hostlist.c_str());
  if (!fs.is_open()) {
    Log_Fatal("Servers file cannot be open.");
  }
  std::string line;
  while (!fs.eof()) {
    getline(fs, line);
    if (line == "") continue;
    line = line + ":" + util::StringPrintf("%d", get_rtmserver_port());
//    Log_Debug("host: %s", line.c_str());
    server_list.push_back(line);
  }
  fs.close();
  return server_list;
}

}
}
