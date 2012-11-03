#include "rpc/server.h"
#include "util/logging.h"

#include <utility>
#include <boost/thread.hpp>

namespace rtm {
namespace rpc {

using std::make_pair;
using namespace ::rtm::util;

Server::Server() :
    serverSocket_(NULL) {
}

static int g_perf_counter = 0;

static void incrPerfCounter() {
  const int report_interval = 20000;
  static int last_report_snapshot = 0;
  static double last_report_time = -1;

  // use gcc builtin functions to do incr counter
  // did not use pthread locking, because of its overhead
  int perf_counter_snapshot = __sync_add_and_fetch(&g_perf_counter, 1);

  if (perf_counter_snapshot % report_interval == 0) {
    double now = Now();
    if (last_report_time > 0) {
      double time_diff = now - last_report_time;
      int counter_diff = perf_counter_snapshot - last_report_snapshot;
      double qps = counter_diff / time_diff;
      Log_Info("QPS: %lf (%d ops in %lf seconds)", qps, counter_diff, time_diff);
    }
    last_report_time = now;
    last_report_snapshot = perf_counter_snapshot;
  }

}

void Server::doDispatch(Socket* client, RPCMessage* req) {
  //Log_Info("Got request, dispatching... method=%s, args=%s", req->header.method, req->data.c_str());
  std::string rBytes = dispatch(req->header.method,
      util::StringPiece(req->payload, req->header.len));
  RPCMessage *result = RPCMessage::alloc(rBytes.size());
  memcpy(result->payload, rBytes.data(), rBytes.size());
  Log_Debug("Response ... %s", rBytes.c_str());

  Log_Debug("Dispatch done, responding...");
  strcpy(result->header.method, req->header.method);
  result->header.id = req->header.id;
  result->header.len = rBytes.size();
  Log_Debug("Payload len = %d", result->header.len);
  client->write(result);
  Log_Debug("Sent response...");
  incrPerfCounter();
}

void Server::pushDispatch(Socket* client, RPCMessage* req) {
//  Log_Assert(repeat_.find(make_pair(client, req->header.id)) == repeat_.end(), "Tried to add the same request twice.");
//  repeat_.insert(make_pair(client, req->header.id));
  dispatchPool_.runAsync(boost::bind(&Server::doDispatch, this, client, req));
}

void Server::serve(int port) {
  serverSocket_ = new ServerSocket(port);
  serverSocket_->listen();

  for (;;) {
    Socket* client = serverSocket_->accept();
    client->setReadHandler(boost::bind(&Server::pushDispatch, this, client, _1));
//    client->setReadHandler(boost::bind(&Server::doDispatch, this, client, _1));
    client->connect();
  }
}

} // namespace rpc
} // namespace rtm
