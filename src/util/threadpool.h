#ifndef UTIL_THREADPOOL_H
#define UTIL_THREADPOOL_H

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include <deque>

namespace rtm {

template<class T>
class WorkQueue {
  std::deque<T> q;
  boost::condition_variable notEmpty_;
  boost::mutex qLock;

public:
  void push(const T& e) {
    {
      boost::mutex::scoped_lock l(qLock);
      q.push_back(e);
      notEmpty_.notify_one();
    }
  }

  T pop() {
    boost::unique_lock<boost::mutex> l(qLock);
    while (q.size() == 0) {
      notEmpty_.wait(l);
    }
    T ret = q.front();
    q.pop_front();
    return ret;
  }
};

class ThreadPool: private boost::noncopyable {
  std::vector<boost::thread*> threads_;

  typedef boost::function<void()> Job;
  WorkQueue<Job> jobs_;

  void runWorkerThread();
public:
  ThreadPool(int size = 80);
  ~ThreadPool();

  void runAsync(Job f) {
    jobs_.push(f);
  }
};

}  // namespace rtm

#endif // UTIL_THREADPOOL_H
