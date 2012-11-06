#include "timequeue.h"
#include <limits>
#include <assert.h>

namespace rtm {
namespace time {

class TimeQueue;
TimeQueue::TimeQueue() {
  assert(pthread_mutex_init(&qLock, NULL) == 0);
  assert(pthread_cond_init(&newfirst_, NULL) == 0);
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
  pthread_mutex_lock(&qLock);
  Log_Debug("Prepare to pushing");

  if (time::TrueTime::GET()->after(e.second)) { // outdated
    (e.first)(true);
  } else {
    if (q_.empty() || e.second < q_.top().second) {
      q_.push(e);
      pthread_cond_signal(&newfirst_);
    } else {
      q_.push(e);
    }
  }
  pthread_mutex_unlock(&qLock);
}

void TimeQueue::pop() {
  pthread_mutex_lock(&qLock);
  while (1) {
    Log_Debug("Waiting for the push ...");
    while (q_.size() == 0) {
      pthread_cond_wait(&newfirst_, &qLock);
    }

    int rc = 0;
    double oldfirst = q_.top().second;
    TimedJob timed_job = q_.top();

    while (q_.top().second >= oldfirst && rc == 0) {
      Log_Debug("Waiting for the newfirst or timer ...");
      timespec timer = time::TrueTime::GET()->fire_localtime(timed_job.second);
      rc = pthread_cond_timedwait(&newfirst_, &qLock, &timer);
    }
    if (rc == ETIMEDOUT) { // fire
      Job job = timed_job.first;
      job(false);
      q_.pop();
      break;
    } else if (q_.top().second < oldfirst) { // newfirst preempts
      // continue;
    } else {
      Log_Fatal("Unknown waken up. ");
    }
  }

  pthread_mutex_unlock(&qLock);
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
