#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "xmlparser.h"
#include <string>
#include <list>

namespace rtm {
namespace util {

class Conf {
public:
  static const std::string conf_file;
  static std::string get_timeserver_host();
  static std::string get_timeserver_hostport();
  static int get_timeserver_port();
  static int get_rtmserver_port();
  static std::list<std::string> get_rtmserver_hostport();
};

}
}
#endif /* CONFIGURATION_H_ */
