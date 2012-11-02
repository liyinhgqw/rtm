#ifndef RTM_SOCKET_H_
#define RTM_SOCKET_H_

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <algorithm>
#include <cinttypes>
#include <deque>
#include <set>
#include <poll.h>
#include <string>

#include "util/common.h"
#include "util/marshal.h"
#include "util/string.h"

namespace rtm {
namespace rpc {

static const size_t kSocketBufferBytes = 128000;
static const size_t kMethodNameSize = 32;

#pragma pack(push, 1)
struct RPCHeader {
  RPCHeader() :
      id(0), len(0) {
  }
  uint64_t id;
  uint32_t len;
  char method[kMethodNameSize];
};

class RPCMessage {
private:
  RPCMessage() {
  }
  ~RPCMessage() {
  }

public:
  static RPCMessage* alloc(uint32_t payloadSize) {
    RPCMessage * m = reinterpret_cast<RPCMessage*>(malloc(
        sizeof(RPCHeader) + payloadSize));
    m->header.len = payloadSize;
    return m;
  }

  static void free(RPCMessage* m) {
    ::free(m);
  }

  size_t totalSize() const {
    return sizeof(RPCHeader) + header.len;
  }

  RPCHeader header;
  char payload[0];

};
#pragma pack(pop)

struct MessageReader {
  RPCMessage *buffer;
  uint32_t headerPos;
  uint32_t messagePos;
  bool allocated;

  MessageReader() {
    reset();
  }

  void reset();
  char* writePointer();
  uint32_t bytesLeft() const;
  const RPCHeader* header() const;

  // Allocate space for the current message.
  void allocate();
};

// set a file descriptor (mostly a socket) to non-blocking mode
void setnonblocking(int fd);

struct PollListener {
  // Return false if the operation failed and this should be removed
  // from the poll loop.
  virtual void handleRead() = 0;
  virtual void handleWrite() = 0;
  virtual int fd() = 0;

  virtual bool hasError() = 0;
  virtual bool needsWrite() = 0;
  virtual bool needsRead() {
    return true;
  }
};

class PollServer {
public:
  PollServer() {
    Log_Assert(pipe(wakeUpPipe_) == 0,
        "Failed to create the wakeUpPipe in PollServer!");
//    Log_Info("wakeUpPipe created: %d, %d", wakeUpPipe_[0], wakeUpPipe_[1]);
    wakeUpSent_ = false;
  }

  void run();
  void add(PollListener* p);
  void remove(PollListener* p);
  void wakeUp();
private:
  typedef boost::unordered_set<PollListener*> ListenSet;
  ListenSet pendingAdd_;
  ListenSet pendingDel_;
  ListenSet current_;

  boost::mutex pendingLock_;

  // use a pipe to wake up the long epoll_wait
  int wakeUpPipe_[2];
  bool wakeUpSent_;
};

extern PollServer* defaultPollServer_;
void InitializeNetworking();

class Socket: public PollListener {
public:
  struct Buffer {
    Buffer() :
        writePos(0), readPos(0) {
    }
    char data[kSocketBufferBytes];

    uint32_t writePos;
    uint32_t readPos;

    uint32_t capacity() const {
      return kSocketBufferBytes;
    }

    bool full() const {
      return writePos == capacity();
    }

    uint32_t readInto(char* dst, uint32_t count);
    uint32_t writeFrom(const char* src, uint32_t count);
  };

  typedef std::deque<Buffer*> BufferList;

  Socket(int fd) {
    reset();
    fd_ = fd;
    host_ = "*remote client*";
  }

  Socket(const std::string& host, int port) {
    reset();
    host_ = host;
    port_ = port;
  }

  void reset() {
    eof_ = false;
    error_ = false;
    fd_ = -1;
    host_ = "*invalid*";
    port_ = -1;
    readHandler_ = NULL;
    writePos_ = 0;
  }

  void write(const RPCMessage* m);
  void connect();

  int fd() {
    return fd_;
  }

  void handleRead();
  void handleWrite();

  bool needsWrite() {
    return !outgoing_.empty();
  }

  bool hasError() {
    return error_ || eof_;
  }

  typedef boost::function<void(RPCMessage*)> ReadHandler;
  void setReadHandler(ReadHandler r) {
    readHandler_ = r;
  }

private:
  void processMessages();
  int readBytes(void* dst, int64_t count);

  std::string peekOutgoing();

//  MessageReader pendingMsg_;

  bool eof_;
  bool error_;

  int fd_;

  std::string host_;
  int port_;

  size_t writePos_;
  std::string outBuffer_;
  std::deque<char> inBytes_;

  std::deque<const RPCMessage*> outgoing_;

  boost::mutex messageLock_;
  boost::condition_variable messageReady_;

  ReadHandler readHandler_;
};

class ServerSocket {
public:
  ServerSocket(int port);
  void listen();
  Socket* accept();
  int fd();

private:
  int port_;
  int serverFd_;
};

}  // namespace rpc
}  // namespace rtm

#endif /* RTM_SOCKET_H_ */
