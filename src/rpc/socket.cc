#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>

#include "rpc/socket.h"

namespace rtm {
namespace rpc {

using util::ToString;
using util::Sleep;
using util::StringPrintf;

PollServer* defaultPollServer_(NULL);
boost::thread *pollThread_(NULL);

void InitializeNetworking() {
  defaultPollServer_ = new PollServer;
  pollThread_ = new boost::thread(&PollServer::run, defaultPollServer_);
}

char* MessageReader::writePointer() {
  return reinterpret_cast<char*>(buffer) + headerPos + messagePos;
}

uint32_t MessageReader::bytesLeft() const {
  return header()->len - messagePos;
}

void MessageReader::allocate() {
  if (!allocated) {
    RPCMessage* temp = buffer;
    buffer = RPCMessage::alloc(temp->header.len);
    memcpy(buffer, temp, sizeof(RPCHeader));
    RPCMessage::free(temp);
  }
}

const RPCHeader* MessageReader::header() const {
  if (headerPos < sizeof(RPCHeader)) {
    return NULL;
  }

  return &buffer->header;
}

void MessageReader::reset() {
  buffer = RPCMessage::alloc(0);
  headerPos = 0;
  messagePos = 0;
  allocated = false;
}

void PollServer::run() {
  int epfd = epoll_create(1000); // any value > 0 will do
  const int kMaxEvents = 100;
  struct epoll_event events[kMaxEvents];

  const int kEpollTimeout = 1000; // ms

  struct epoll_event ev;

  // register the wake up pipe
  ev.events = EPOLLIN;
  ev.data.ptr = wakeUpPipe_; // well, this looks stupid =.=
  epoll_ctl(epfd, EPOLL_CTL_ADD, wakeUpPipe_[0], &ev);

  std::vector<PollListener*> bad;
  for (;;) {
    bad.clear();
    int nfds = epoll_wait(epfd, events, kMaxEvents, kEpollTimeout);
    for (int i = 0; i < nfds; i++) {
      if (events[i].data.ptr == wakeUpPipe_) {
        char readBuf[10000];
        read(wakeUpPipe_[0], readBuf, 10000);
        continue;
      }
      PollListener* l = (PollListener *) events[i].data.ptr;
      if (events[i].events & EPOLLIN)
        l->handleRead();
      if (events[i].events & EPOLLOUT)
        l->handleWrite();

      if (l->hasError() || (events[i].events & (EPOLLERR | EPOLLHUP))) {
        bad.push_back(l);
      }
    }

    for (std::vector<PollListener*>::iterator it = bad.begin(); it != bad.end();
        ++it) {
      epoll_ctl(epfd, EPOLL_CTL_DEL, (*it)->fd(), NULL);
      current_.erase(*it);
    }

    boost::mutex::scoped_lock sl(pendingLock_);
    // let del goes before add, in case some fd is deleted and
    // immediately added (possible?)
    for (ListenSet::iterator it = pendingDel_.begin(); it != pendingDel_.end();
        ++it) {
      epoll_ctl(epfd, EPOLL_CTL_DEL, (*it)->fd(), NULL);
    }
    for (ListenSet::iterator it = pendingAdd_.begin(); it != pendingAdd_.end();
        ++it) {
      ev.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP;
      ev.data.ptr = *it;
      epoll_ctl(epfd, EPOLL_CTL_ADD, (*it)->fd(), &ev);
    }

    for (ListenSet::iterator it = current_.begin(); it != current_.end();
        ++it) {
      ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
      ev.data.ptr = *it;
      if ((*it)->needsWrite()) {
        ev.events |= EPOLLOUT;
      }
      Log_PAssert(epoll_ctl(epfd, EPOLL_CTL_MOD, (*it)->fd(), &ev) == 0,
          "Failed to modify epoll set!");
    }

    pendingDel_.clear();
    pendingAdd_.clear();
    wakeUpSent_ = false;

//    PERIODIC(5, Log_Info("Poll server running, with %d active listeners.", current_.size()));
  }
}

void PollServer::add(PollListener* p) {
  boost::mutex::scoped_lock l(pendingLock_);
  //    Log_Assert(listeners_.find(p) == listeners_.end(), "Tried to add the same listener twice.");
  pendingAdd_.insert(p);
  current_.insert(p);
  wakeUp();
}

// wake up the underlying epoll_wait
void PollServer::wakeUp() {
  if (!wakeUpSent_) {
    char ch = 'y';
    Log_Assert(write(wakeUpPipe_[1], &ch, 1) == 1,
        "Failed to send wake up message to epoll! %s, pipeFd = %d",
        strerror(errno), wakeUpPipe_[0]);
    wakeUpSent_ = true;
  }
}

void PollServer::remove(PollListener* p) {
  boost::mutex::scoped_lock l(pendingLock_);
  Log_Assert(current_.find(p) != current_.end(),
      "Tried to remove non-existent listener.");
  pendingDel_.insert(p);
  current_.erase(p);
  wakeUp();
}

ServerSocket::ServerSocket(int port) {
  serverFd_ = socket(AF_INET, SOCK_STREAM, 0);
  int v = 1;
  setsockopt(serverFd_, SOL_SOCKET, SO_REUSEADDR, &v, sizeof(v));
  setsockopt(serverFd_, IPPROTO_TCP, TCP_NODELAY, &v, sizeof(v));
  sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_port = htons(port);
  local.sin_addr.s_addr = INADDR_ANY;
  bind(serverFd_, (struct sockaddr*)&local, sizeof(local));
  port_ = port;
}

void ServerSocket::listen() {
  Log_Debug("Listening on port %d", port_);
  Log_PAssert(::listen(serverFd_, 32) == 0, "Error trying to listen.");
}

Socket* ServerSocket::accept() {
  struct sockaddr_in clientAddr;
  int len = sizeof(clientAddr);
  int fd = ::accept(serverFd_, (struct sockaddr*) (&clientAddr),
      (socklen_t*) (&len));
  setnonblocking(fd);
  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
  Log_Debug("Accepted new connection: %d", fd);
  Socket* s = new Socket(fd);
  Log_Assert(fd != -1, "Invalid return value from accept().");
  return s;
}

int ServerSocket::fd() {
  return serverFd_;
}

void Socket::connect() {
  if (fd_ == -1) {
    Log_Assert(port_ != -1, "Trying to connect on server socket.");
    while (1) {
      Log_Debug("Connecting to %s:%d", host_.c_str(), port_);
      struct addrinfo addrHint, *addrResult;
      memset(&addrHint, 0, sizeof(addrHint));
      addrHint.ai_family = AF_INET;
      addrHint.ai_socktype = SOCK_STREAM;
      addrHint.ai_flags = 0;
      addrHint.ai_protocol = 0;

      int gaiRes = getaddrinfo(host_.c_str(), ToString(port_).c_str(), &addrHint, &addrResult);
      Log_Assert(gaiRes == 0,
        "Failed to retrieve address information for %s:%d: %s", host_.c_str(), port_, gai_strerror(gaiRes));
      struct addrinfo *rp;
      for (rp = addrResult; rp != NULL; rp = rp->ai_next) {
        fd_ = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd_ != -1) {
          break;
        }
      }

      Log_Assert(fd_ != -1, "Failed to get socket.");

      int res = ::connect(fd_, rp->ai_addr, rp->ai_addrlen);
      if (res == 0) {
        int v = 1;
        fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL, 0) | O_NONBLOCK);
        setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &v, sizeof(v));
        freeaddrinfo(addrResult);
        Log_Debug("Connected to %s:%d.", host_.c_str(), port_);
        break;
      }
      Log_Debug("Failed to connect, sleeping...");
      Sleep(1);
    }
  }

  error_ = false;
  eof_ = false;
  defaultPollServer_->add(this);
}

uint32_t Socket::Buffer::readInto(char* dst, uint32_t count) {
  uint32_t bytes = std::min(count, writePos - readPos);
  memcpy(dst, data + readPos, bytes);
  readPos += bytes;
  return bytes;
}

uint32_t Socket::Buffer::writeFrom(const char* src, uint32_t count) {
  uint32_t bytes = std::min(count, capacity() - writePos);
  memcpy(data + writePos, src, bytes);
  writePos += bytes;
  return bytes;
}

int Socket::readBytes(void* dst, int64_t count) {
  Log_Assert(!eof_ && !error_, "Trying to read from broken socket.");
  int bytesRead = ::read(fd_, dst, count);
  if (bytesRead == 0) {
    eof_ = true;
    Log_Error("Reached EOF for socket.");
  }
  if (bytesRead < 0) {
    if (errno != EAGAIN) {
      error_ = true;
      eof_ = true;
      Log_Perror("Error reading from socket.");
    }
  }
  return bytesRead;
}

void Socket::handleRead() {
  if (hasError())
    return;

  if (error_ || eof_) {
    Log_Error("Socket error detected.  Closing.");
    Log_Error("TODO/ should probably try reconnecting.  or something.");
    return;
  }

//  if (incomingBytes_.empty() || incomingBytes_.back()->full()) {
//    incomingBytes_.push_back(new Buffer);
//  }
//
//  Buffer* b = incomingBytes_.back();
//  int bytesRead = readBytes(b->data + b->writePos, b->capacity() - b->writePos);
//  if (bytesRead > 0) {
//    b->writePos += bytesRead;
//  }

  char buf[kSocketBufferBytes];
  int bytesRead = readBytes(buf, kSocketBufferBytes);
  if (bytesRead > 0) {
    inBytes_.resize(inBytes_.size() + bytesRead);
    std::copy(buf, buf + bytesRead, inBytes_.end() - bytesRead);
  }

  // Try to extract any messages we just read in.
  processMessages();
}

void Socket::processMessages() {
  while (inBytes_.size() >= sizeof(RPCHeader)) {
    RPCHeader h;
    std::copy(inBytes_.begin(), inBytes_.begin() + sizeof(RPCHeader),
        reinterpret_cast<char*>(&h));

    if (inBytes_.size() < h.len + sizeof(RPCHeader)) {
      break;
    }

    inBytes_.erase(inBytes_.begin(), inBytes_.begin() + sizeof(RPCHeader));

    RPCMessage* m = RPCMessage::alloc(h.len);
    memcpy(&m->header, &h, sizeof(RPCHeader));
    std::copy(inBytes_.begin(), inBytes_.begin() + h.len,
        reinterpret_cast<char*>(m->payload));
    inBytes_.erase(inBytes_.begin(), inBytes_.begin() + h.len);

    Log_Info("Read message... %s", m->header.method);
    readHandler_(m);
  }
}

void Socket::handleWrite() {
  if (hasError())
    return;

  Log_Assert(!error_, "Trying to write on broken socket.");
  if (outBuffer_.size() < kSocketBufferBytes) {
    outBuffer_.resize(kSocketBufferBytes);
  }

//  Log_Info("Writing... %d %d", writePos_, outBuffer_.size());
  while (!outgoing_.empty() && writePos_ != outBuffer_.size()) {
    const RPCMessage* m;
    {
      boost::mutex::scoped_lock lock(messageLock_);
      m = outgoing_.front();
      outgoing_.pop_front();
    }

    if (outBuffer_.size() - writePos_ < m->totalSize()) {
      outBuffer_.resize(writePos_ + m->totalSize());
    }

    memcpy(&outBuffer_[writePos_], m, m->totalSize());
    writePos_ += m->totalSize();

    RPCMessage::free((RPCMessage*)m);
  }

  int bytesWritten = ::write(fd_, outBuffer_.data(), writePos_);
//  Log_Info("Writing... %d, %d, %d", writePos_, outBuffer_.size(), bytesWritten);
  if (bytesWritten <= 0) {
    if (errno != EAGAIN) {
      error_ = true;
      Log_Perror("Error writing to socket.");
    }
  } else {
    if (bytesWritten == writePos_) {
      outBuffer_.clear();
    } else {
      outBuffer_.erase(outBuffer_.begin(), outBuffer_.begin() + bytesWritten);
    }
    writePos_ -= bytesWritten;
  }
}

void Socket::write(const RPCMessage *m) {
  {
    boost::mutex::scoped_lock lock(messageLock_);
    outgoing_.push_back(m);
  }
  defaultPollServer_->wakeUp();
}

void setnonblocking(int fd) {
#ifdef O_NONBLOCK
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {
    perror("setnonblocking(): fcntl GET failed!");
  }
  int ok = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  if (ok == -1) {
    perror("setnonblocking(): fcntl SET failed!");
  }
#else   // O_NONBLOCK
  int yes = 1;
  if (ioctl(fd, FIOBIO, &yes) == -1) {
    perror("setnonblocking(): ioctl failed!");
  }
#endif  // O_NONBLOCK
}

}  // namespace rpc
}  // namespace rtm
