#include "util/threadpool.h"

namespace rtm {

ThreadPool::ThreadPool(int size /* = 16 */) {
  threads_.resize(size);
  for (size_t i = 0; i < threads_.size(); i++) {
    threads_[i] = new boost::thread(&ThreadPool::runWorkerThread, this);
  }
}

ThreadPool::~ThreadPool() {
  for (size_t i = 0; i < threads_.size(); ++i) {
    this->jobs_.push(NULL);  // suicide symbol
  }
  for (size_t i = 0; i < threads_.size(); i++) {
    threads_[i]->join();
    delete threads_[i];
  }
}

void ThreadPool::runWorkerThread() {
  for (;;) {
    Job j = this->jobs_.pop();
    if (j == NULL) {
      break;
    }
    j();
  }
}


CallbackThreadPool::CallbackThreadPool(int size /* = 16 */) {
  threads_.resize(size);
  for (size_t i = 0; i < threads_.size(); i++) {
    threads_[i] = new boost::thread(&CallbackThreadPool::runWorkerThread, this);
  }
}

CallbackThreadPool::~CallbackThreadPool() {
  for (size_t i = 0; i < threads_.size(); i++) {
    threads_[i]->join();
    delete threads_[i];
  }
}

void CallbackThreadPool::runWorkerThread() {
  for (;;) {
    CB_Job cb_j = this->jobs_.pop();
    if (cb_j == NULL) {
      break;
    }
    bool ret = (cb_j.first)();
    // ugly code I admit
    Callback& cb = cb_j.second;
    ++ cb.first;      // total callback
    if (ret) ++ cb.second;  // ret
  }
}

}  // namespace rtm

