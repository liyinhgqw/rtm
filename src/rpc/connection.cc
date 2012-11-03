#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "connection.h"
#include "future.h"
#include "util/logging.h"
#include "server.h"

using std::string;

namespace rtm {
namespace rpc {

Endpoint EndpointHelper::rtm(const string& hostport) {
  Endpoint c;
  std::vector<util::StringPiece> parts = util::StringPiece::split(hostport, ":");
  c.host = parts[0].str();
  c.port = strtol(parts[1].str().c_str(), NULL, 0);
  c.protocol = "rtm";
  c.localServer = (int64_t) NULL;
  return c;
}

Endpoint EndpointHelper::local(const Server* s) {
  Endpoint c;
  c.protocol = "local";
  c.localServer = reinterpret_cast<int64_t>(s);
  return c;
}

class TCPConnection: public Connection {
private:
  Socket* socket_;
  int64_t sequenceNumber_;

  boost::mutex msgLock_;
  boost::condition_variable msgReady_;
  typedef boost::unordered_map<int64_t, RPCMessage*> ResponseMap;
  typedef boost::unordered_map<int64_t, Future*> WaitingMap;
  WaitingMap waiting_;
  ResponseMap received_;

  std::string host_;
  int port_;

public:
  TCPConnection(const std::string& host, int port);
  TCPConnection(const std::string& hostport);
  ~TCPConnection();

  virtual void send(Future* result, const util::StringPiece& method,
      const util::StringPiece& args);
  virtual void wait(Future* f);

  void readFinished(RPCMessage* m) {
    boost::mutex::scoped_lock l(msgLock_);
    received_.insert(std::make_pair(m->header.id, m));
    msgReady_.notify_all();
  }
};

class LocalConnection: public Connection {
private:
  Server* server_;
public:
  LocalConnection(Server* s);

  virtual void send(Future* f, const util::StringPiece& method,
      const util::StringPiece& args);
  virtual void receiveOne(double timeout);
  virtual void wait(Future* f);
};

Connection* Connection::create(const Endpoint& e) {
  Log_Debug("Connecting to %s:%s", e.protocol.c_str(), e.host.c_str());
  if (e.protocol == "rtm") {
    return new TCPConnection(e.host, e.port);
  } else if (e.protocol == "local") {
    return new LocalConnection(reinterpret_cast<Server*>(e.localServer));
  } else {
    Log_Fatal("Invalid connection protocol: %s", e.protocol.c_str());
  }
  return NULL;
}

TCPConnection::~TCPConnection() {
  delete socket_;
}

TCPConnection::TCPConnection(const string& host, int port) {
  sequenceNumber_ = 0;
  socket_ = new Socket(host, port);
  host_ = host;
  port_ = port;
  socket_->setReadHandler(boost::bind(&TCPConnection::readFinished, this, _1));
  Log_Debug("Set up socket.");
  socket_->connect();
}

TCPConnection::TCPConnection(const string& hostport) {
  sequenceNumber_ = 0;
  std::vector<util::StringPiece> parts = util::StringPiece::split(hostport, ":");
  host_ = parts[0].str();
  port_ = strtod(parts[1].data(), NULL);
  socket_ = new Socket(host_, port_);
  socket_->setReadHandler(boost::bind(&TCPConnection::readFinished, this, _1));
  socket_->connect();
}

void TCPConnection::send(Future* result, const util::StringPiece& method,
    const util::StringPiece& args) {

  RPCMessage* msg = RPCMessage::alloc(args.size());
  {
    boost::mutex::scoped_lock l(msgLock_);
    msg->header.id = sequenceNumber_++;
  }

  msg->header.len = args.size();
  Log_Assert(method.size() < kMethodNameSize, "Too long a method name.");
  Log_Assert(args.size() > 0, "Invalid payload?");
  bzero(msg->header.method, kMethodNameSize);
  strcpy(msg->header.method, method.str().c_str());
  memcpy(msg->payload, args.data(), args.size());

  Log_Assert(msg->header.len > 0, "This shouldn't happen.");
  result->init(this, msg->header.id);
  socket_->write(msg);
}

void TCPConnection::wait(Future* f) {
  Log_Debug("Waiting for %d", f->id);

  while (1) {
    {
      boost::unique_lock<boost::mutex> l(msgLock_);
      ResponseMap::iterator i = received_.find(f->id);
      if (i != received_.end()) {
        break;
      }
    }

    if (f->timeLeft() <= 0) {
      f->errorTrace.push_back(RPCError("Timed out"));
      f->status = kCallTimedOut;
      return;
    }

    util::Sleep(0.001);
  }

  RPCMessage* msg;
  {
    boost::mutex::scoped_lock l(msgLock_);
    ResponseMap::iterator i = received_.find(f->id);
    msg = i->second;
    received_.erase(i);
  }
  Log_Debug("Read Message ... len = %d", msg->header.len);
  util::StringPiece str(msg->payload, msg->header.len);
  Log_Debug("ret string = %s", str.str().c_str());
  f->read(util::StringPiece(msg->payload, msg->header.len));
  Log_Debug("Read done .");
  RPCMessage::free(msg);
}

LocalConnection::LocalConnection(Server * s) {
  server_ = s;
}

void LocalConnection::wait(Future* f) {
}

void LocalConnection::receiveOne(double timeout) {
}

void LocalConnection::send(Future* f, const util::StringPiece& method,
    const util::StringPiece& args) {
  f->connection = this;
  f->id = 0;
  string response = server_->dispatch(method, args);
  Log_Debug("Local read for future %p", &f);
  f->read(response);
  Log_Debug("Done.");
}

RPCError::RPCError() {
  this->hostname = util::Hostname();
  this->time = util::Now();
  this->filename = "*unknown*";
  this->lineNumber = -1;
}

RPCError::RPCError(const string& msg) {
  this->hostname = util::Hostname();
  this->time = util::Now();
  this->filename = "*unknown*";
  this->lineNumber = -1;
  this->msg = msg;
}

string RPCError::traceAsString(const std::vector<RPCError>& trace) {
  string lines;
  for (size_t i = 0; i < trace.size(); ++i) {
    lines += util::StringPrintf("%s:%d - %s\n", trace[i].filename.c_str(),
        trace[i].lineNumber, trace[i].msg.c_str());
  }
  return lines;
}

void Endpoint::write(Encoder* e) const {
  e->write(protocol);
  e->write(host);
  e->write(port);
  e->write(serviceType);
  e->write(localServer);
}

void RPCError::write(Encoder* e) const {
  e->write(msg);
  e->write(hostname);
  e->write(time);
  e->write(filename);
  e->write(lineNumber);
}

void Endpoint::read(Decoder* d) {
  d->read(&protocol);
  d->read(&host);
  d->read(&port);
  d->read(&serviceType);
  d->read(&localServer);
}

void RPCError::read(Decoder* d) {
  d->read(&msg);
  d->read(&hostname);
  d->read(&time);
  d->read(&filename);
  d->read(&lineNumber);
}

} // namespace rpc
} // namespace rtm
