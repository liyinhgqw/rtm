#ifndef STREAM_H_
#define STREAM_H_

#include <stdlib.h>
#include <string>

#include "util/logging.h"
#include "util/string.h"

namespace rtm {
class Stream {
public:
  virtual void seek(uint64_t offset) = 0;
  virtual uint64_t pos() = 0;
  virtual uint64_t size() = 0;
  virtual bool done() = 0;
  virtual void write(const char* buffer, int len) = 0;
  virtual bool read(std::string *buffer, int bytes) {
    buffer->resize(bytes);
    return read(&buffer[0], bytes);
  }
  virtual bool read(char* buffer, int bytes) = 0;

  virtual void mark() = 0;
  virtual void reset() = 0;
};

class StringStream: public Stream {
  std::string* s_;
  util::StringPiece sp_;
  uint64_t pos_;
  uint64_t mark_;

public:
  StringStream(const util::StringPiece& sp) :
      s_(NULL), sp_(sp), pos_(0), mark_(-1) {
  }

  StringStream(std::string* s) :
      s_(s), sp_(s->data()), pos_(0), mark_(-1) {

  }

  bool read(char *buffer, int bytes) {
    if (bytes + pos_ > (int64_t)sp_.size()) {
      Log_Fatal("End of stream!");
      return false;
    }

    memcpy(buffer, sp_.data() + pos_, bytes);
    pos_ += bytes;

    return true;
  }

  void seek(uint64_t offset) {
    pos_ = offset;
  }

  void mark() {
    mark_ = pos_;
  }

  void reset() {
    pos_ = mark_;
  }

  void write(const char* buffer, int len) {
    s_->resize(pos_ + len);
    memcpy(&(*s_)[pos_], buffer, len);
    pos_ += len;
    sp_ = *s_;
  }

  uint64_t pos() {
    return pos_;
  }

  uint64_t size() {
    return sp_.size();
  }

  bool done() {
    return (int64_t)sp_.size() == pos_;
  }
};

}

#endif /* STREAM_H_ */
