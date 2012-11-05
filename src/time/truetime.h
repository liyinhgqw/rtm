#ifndef TRUETIME_H_
#define TRUETIME_H_

#include "util/common.h"
#include "util/marshal.h"

namespace rtm {
namespace time {

class TrueTime: public Serializable {


public:
  static const double err;     // err confidence interval

  TrueTime() { offset = 0.0; }
  timespec now() const;
  double d_now() const;

  bool after(double) const;
  bool after(const timespec&) const;
  bool before(double) const;
  bool before(const timespec&) const;

  timespec fire_time(double) const;
  timespec fire_localtime(double) const;

  static double deadline(double);
  static double deadline(const timespec&);

  static TrueTime* GET();
  virtual void write(Encoder *e) const;
  virtual void read(Decoder *d);


private:
  double offset;  // different time duration compared to the global clock
};

//const double TrueTime::err = 0.01;


}
}


#endif /* TRUETIME_H_ */