#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace rtm {
namespace util {

using boost::property_tree::ptree;

class XmlParser {
public:
  XmlParser(std::string = std::string(getenv("RTM_HOME"))+"/conf/rtm.xml");
  static ptree parser(const std::string filename);

  template <class T>
  static T parse(const std::string filename, const std::string element,
                 typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
    T v;
    if (boost::is_integral<T>::value)
      v = XmlParser::parser(filename).get(element, 0);
    else if (boost::is_float<T>::value)
      v = XmlParser::parser(filename).get(element, 0.0);
    else
      throw new std::exception;
    return v;
  }

  static std::string parse(const std::string filename, const std::string element);

  void set_file(std::string);
  ptree parser();

  template <class T>
  T parse(const std::string element,
          typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
    T v;
    if (boost::is_integral<T>::value)
      v = XmlParser::parser(file_).get(element, 0);
    else if (boost::is_float<T>::value)
      v = XmlParser::parser(file_).get(element, 0.0);
    else
      throw new std::exception;
    return v;
  }
  std::string parse(const std::string element);

  template <class T>
  T read(typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
    printf("bingo\n");
  }

private:
  std::string file_;
};


}
}

#endif /* XMLPARSER_H_ */
