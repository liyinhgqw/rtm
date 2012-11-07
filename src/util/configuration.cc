#include "configuration.h"

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

}
}
