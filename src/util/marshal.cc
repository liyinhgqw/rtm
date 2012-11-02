#include "util/marshal.h"
#include "util/string.h"

namespace rtm {
Decoder::Decoder(const std::string& data) :
    src_(new StringStream(data)) {
}

Decoder::Decoder(util::StringPiece s) :
    src_(new StringStream(s)) {
}

void Decoder::read_bytes(char* b, int len) {
  src_->read(b, len);
}

void Decoder::read_string(std::string* v) {
  uint32_t len = read<int32_t>();
  v->resize(len);
  read_bytes(&(*v)[0], len);
}

bool Decoder::done() {
  return src_->done();
}

size_t Decoder::pos() {
  return src_->pos();
}

void Decoder::seek(int p) {
  src_->seek(p);
}

Encoder::Encoder(std::string* s) :
    out_(new StringStream(s)) {
}

size_t Encoder::pos() {
  return out_->size();
}

void Encoder::write_string(util::StringPiece v) {
  write((int32_t) v.size());
  write_bytes(v);
}

void Encoder::write_bytes(util::StringPiece s) {
  write_bytes(s.data(), s.size());
}

void Encoder::write_bytes(const char* a, int len) {
  out_->write(a, len);
}

void Encoder::write(const std::string& s) {
  write_string(s);
}

void Encoder::write(util::StringPiece s) {
  write_string(s);
}


}
