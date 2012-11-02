#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <vector>
#include <string>
#include <memory.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <boost/functional/hash.hpp>

namespace rtm {
namespace util {

using std::string;

class StringPiece {
public:
  StringPiece();
  StringPiece(const StringPiece& s);
  StringPiece(const string& s);
  StringPiece(const string& s, int len);
  StringPiece(const char* c);
  StringPiece(const char* c, int len);

  // Remove whitespace from either side
  void strip();

  uint64_t hash() const;
  string AsString() const;
  string str() const {
    return AsString();
  }

  int size() const {
    return len_;
  }

  const char* data() const {
    return data_;
  }

  static std::vector<StringPiece> split(StringPiece sp, StringPiece delim);
  static uint64_t hash(const StringPiece& sp);
private:
  const char* data_;
  int len_;
};

bool operator==(const StringPiece& a, const char* b);
bool operator==(const StringPiece& a, const StringPiece& b);

void MurmurHash3(const void * key, int len, uint32_t seed, void * out);

const char* strnstr(const char* haystack, const char* needle, int len);

template<class Iterator>
string JoinString(Iterator start, Iterator end, string delim = " ") {
  string out;
  while (start != end) {
    out += *start;
    ++start;
    if (start != end) {
      out += delim;
    }
  }
  return out;
}

string StringPrintf(StringPiece fmt, ...);
string VStringPrintf(StringPiece fmt, va_list args);

string ToString(int32_t);
string ToString(int64_t);
string ToString(string);
string ToString(StringPiece);

static inline std::size_t hash_value(StringPiece const& s) {
  return s.hash();
}

} // namespace util
} // namespace rtm

#endif
