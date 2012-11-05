#include "truetime.h"
#include "util/logging.h"

namespace rtm {
namespace time {

void InitializeTrueTime() {
  TrueTime::GET();
}

TrueTime* TrueTime::GET() {
  static TrueTime* r = NULL;
  if (!r) {
    r = new TrueTime();
  }
  return r;
}

const double TrueTime::err = 0.01;

timespec TrueTime::now() const
{
  return util::timespecFromDouble(d_now());
}

double TrueTime::d_now() const
{
  double local = util::Now();
  double global = local + offset;
  return global;
}

bool TrueTime::after(double t) const
{
  return d_now() - t > 2 * err;
}

bool TrueTime::after(const timespec& t) const
{
  return d_now() - util::timespecToDouble(t) > 2 * err;
}


bool TrueTime::before(double t) const
{
  return t - d_now() > 2 * err;
}

bool TrueTime::before(const timespec& t) const
{
  return util::timespecToDouble(t) - d_now() > 2 * err;
}

void TrueTime::write(Encoder *e) const {
  double dnow = d_now();
  //e->write(dnow);
}

void TrueTime::read(Decoder *d) {
  Log_Fatal("Not implemented: TrueTime read. ");
}

timespec TrueTime::fire_time(double cl_time) const {
  return util::timespecFromDouble(deadline(cl_time));
}

timespec TrueTime::fire_localtime(double cl_time) const {
  double d_localtime = deadline(cl_time) - offset;
  return util::timespecFromDouble(d_localtime);
}

double TrueTime::deadline(double cl_time) {
  return cl_time + 2 * err;
}
double TrueTime::deadline(const timespec& cl_time) {
  return util::timespecToDouble(cl_time) + 2 * err;
}


} // namespace time
} // namespace rtm
