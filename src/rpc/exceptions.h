#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <iostream>
#include <exception>
#include "util/logging.h"

namespace rtm {
namespace rpc {

class rpc_exception: public std::exception {
public:
  virtual void error() const throw() {};
};

class rpc_run_exception: public rpc_exception {
public:
  virtual void error() const throw() {
    Log_Info("rpc_run_exception.");
  }
  virtual const char* what() const throw() {
    return "rpc_run_exception";
  }
};


}
}

#endif /* EXCEPTIONS_H_ */
