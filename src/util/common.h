#ifndef RTM_COMMON_H_
#define RTM_COMMON_H_

#include <boost/function.hpp>

#include <algorithm>
#include <string>
#include <vector>
#include <time.h>

namespace rtm {
namespace util {

static inline uint64_t rdtsc() {
  uint32_t hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return (((uint64_t) hi) << 32) | ((uint64_t) lo);
}

double Now();
std::string Hostname();
timeval timevalFromDouble(double t);
timespec timespecFromDouble(double t);
double timespecToDouble(const timespec&);

void Sleep(double sleepTime);


}  // namespace util
}  // namespace rtm

#endif /* RTM_COMMON_H_ */
