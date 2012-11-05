#ifndef TIMEQUEUE_H_
#define TIMEQUEUE_H_

#include "truetime.h"
#include "util/logging.h"
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <pthread.h>
#include <queue>
#include <vector>
#include <algorithm>

namespace rtm {
namespace time {

using namespace std;

template<class T>
class TimeCmp {
  typedef pair<T, double> TimedPair;
  bool reverse;
public:
  TimeCmp(const bool& revparam=false): reverse(revparam) {}
  bool operator() (const TimedPair& lhs, const TimedPair& rhs) const {
    Log_Assert(lhs.second != rhs.second, "Identical time point !");
    if (reverse) return (lhs.second > rhs.second);
    else return (lhs.second < rhs.second);
  }
};


class TimeQueue: private boost::noncopyable {
private:
  typedef boost::function<void()> Job;
  typedef pair<Job, double> TimedJob;
  priority_queue<TimedJob, vector<TimedJob>, TimeCmp<Job> > q_;
  pthread_cond_t newfirst_;
  pthread_mutex_t qLock;
  boost::thread* workthread_;
  void runWorkerThread();
public:
  TimeQueue();
  void runAsync(Job job, double time);
  void push(TimedJob);
  void pop();
};


} // namespace time
} // namespace rtm

#endif /* TIMEQUEUE_H_ */
