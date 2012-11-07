#include "xmlparser.h"
#include <exception>
#include <stdlib.h>

namespace rtm {
namespace util {

using boost::property_tree::ptree;

XmlParser::XmlParser(std::string filename) {
  file_ = filename;
}

ptree XmlParser::parser(const std::string filename) {
  ptree pt;
  read_xml(filename, pt);
  return pt;
};

std::string XmlParser::parse(const std::string filename, const std::string element) {
  std::string v;
  v = XmlParser::parser(filename).get(element, "");
  return v;
}

ptree XmlParser::parser() {
  ptree pt;
  read_xml(file_, pt);
  return pt;
};


std::string XmlParser::parse(const std::string element) {
  std::string v;
  v = XmlParser::parser(file_).get(element, "");
  return v;
}

void XmlParser::set_file(std::string filename) {
  file_ = filename;
}

}
}
