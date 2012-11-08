#include "timequeue.h"
#include <limits>
#include <assert.h>

namespace rtm {
namespace time {

class TimeQueue;
TimeQueue::TimeQueue() {
  assert(pthread_mutex_init(&qLock_, NULL) == 0);
  assert(pthread_cond_init(&newfirst_, NULL) == 0);
  assert(pthread_cond_init(&notempty_, NULL) == 0);
  workthread_ = new boost::thread(&TimeQueue::runWorkerThread, this);
}

void TimeQueue::runWorkerThread() {
  for (;;) {
    pop();
  }
}

void TimeQueue::runAsync(Job job, double time) {
  push(make_pair(job, time));
}

void TimeQueue::push(TimedJob e) {
  Log_Debug("Prepare to push");
  pthread_mutex_lock(&qLock_);
  Log_Debug("Prepare to pushing");

  if (time::TrueTime::GET()->after(e.second)) { // outdated
    Log_Debug("Outdated");
    (e.first)(true);
  } else {
    Log_Debug("Push job %f", e.second);
    if (q_.empty()) {
      q_.push(e);
      Log_Debug("Signal Notempty.");
      pthread_cond_signal(&notempty_);
    } else if (e.second < q_.top().second) {
      q_.push(e);
      Log_Debug("Signal Newfirst");
      pthread_cond_signal(&newfirst_);
    } else {
      Log_Debug("Pushback");
      q_.push(e);
    }
  }
  pthread_mutex_unlock(&qLock_);
}

void TimeQueue::pop() {
  pthread_mutex_lock(&qLock_);
  while (1) {
    Log_Debug("Waiting for the push ...");
    while (q_.size() == 0) {
      pthread_cond_wait(&notempty_, &qLock_);
    }

    int rc = 0;
    double oldfirst = q_.top().second;
    TimedJob timed_job = q_.top();

    while (q_.top().second >= oldfirst && rc == 0) {
      timespec timer = time::TrueTime::GET()->fire_localtime(timed_job.second);
      Log_Debug("Waiting for the newfirst or timer ... %f", util::timespecToDouble(timer));
      rc = pthread_cond_timedwait(&newfirst_, &qLock_, &timer);
    }
    if (rc == ETIMEDOUT) { // fire
      Log_Debug("Timeout");
      Job job = timed_job.first;
      job(false);
      Log_Debug("Pop job: %f", q_.top().second);
      q_.pop();
      break;
    } else if (q_.top().second < oldfirst) { // newfirst preempts
      Log_Debug("Preempted");
      // continue;
    } else {
      Log_Fatal("Unknown waken up. ");
    }
  }

  pthread_mutex_unlock(&qLock_);
}

// should not happen actually
void TimeQueue::drop_passed() {
  TimedJob tjob;
  while (!q_.empty()) {
    tjob = q_.top();
    if (time::TrueTime::GET()->after(tjob.second)) {
      q_.pop();
    } else {
      break;
    }
  }
}

}
}
