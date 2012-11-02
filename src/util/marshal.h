#ifndef MARSHAL_H_
#define MARSHAL_H_

#include <boost/utility/enable_if.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

#include "util/stream.h"
#include "util/string.h"

namespace rtm {

class Decoder {
private:
  boost::scoped_ptr<Stream> src_;
public:
  Decoder(const std::string& data);
  Decoder(util::StringPiece s);

  template<class T>
  void read(T* r,
      typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
    read_bytes((char*) r, sizeof(T));
  }

  template <class T>
  T read(typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
    T v;
    read_bytes((char*) &v, sizeof(T));
    return v;
  }

  template<class T>
  void peek(T* r,
      typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
    peek_bytes((char*) r, sizeof(T));
  }

  template <class T>
  T peek(typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
    T v;
    peek_bytes((char*) &v, sizeof(T));
    return v;
  }


  void read(std::string* v) {
    read_string(v);
  }

  void peek_bytes(char* b, int len) {
    mark();
    read_bytes(b, len);
    reset();
  }

  void read_bytes(char* b, int len);
  void read_string(std::string* v);

  bool done();
  size_t pos();
  void seek(int p);

  void mark() {
    src_->mark();
  }

  void reset() {
    src_->reset();
  }
};

class Encoder {
private:
  boost::scoped_ptr<Stream> out_;
public:
  Encoder(std::string* s);

  template<class T>
  void write(const T& r,
      typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
    write_bytes((char*) &r, sizeof(T));
  }

  void write(const std::string& v);
  void write(util::StringPiece v);

  void write_string(util::StringPiece v);
  void write_bytes(util::StringPiece s);
  void write_bytes(const char *a, int len);

  size_t pos();
};

// Declarations for the serialization interface.
//
// for all types known to the system.
class Serializable {
public:
  virtual void write(Encoder *e) const = 0;
  virtual void read(Decoder *d) = 0;
};

namespace marshal {

static inline void write(Encoder *e, const Serializable& s) {
  s.write(e);
}

static inline void read(Decoder *d, Serializable& s) {
  s.read(d);
}

static inline void write(Encoder *e, const Serializable* s) {
  s->write(e);
}

static inline void read(Decoder *d, Serializable* s) {
  s->read(d);
}

static inline void write(Encoder* e, const std::string& s) {
  e->write(s);
}

static inline void read(Decoder* d, std::string& s) {
  d->read(&s);
}

template<class T>
static void write(Encoder* e, const T& r,
    typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
  e->write(r);
}

template<class T>
static void read(Decoder* d, T& r,
    typename boost::enable_if<boost::is_arithmetic<T> >::type* dummy = 0) {
  d->read(&r);
}

template<class T>
static void write(Encoder* e, const std::vector<T>& v) {
  write(e, v.size());
  for (typename std::vector<T>::const_iterator i = v.begin(); i != v.end();
      ++i) {
    write(e, *i);
  }
}

template<class T>
static void write(Encoder* e, boost::shared_ptr<T> v) {
  write(e, v.get());
}

template<class T>
static void read(Decoder* d, std::vector<T>* v) {
  size_t vsize;
  read(d, vsize);
  v->resize(vsize);
  for (size_t i = 0; i < v->size(); ++i) {
    read(d, v->at(i));
  }
}

template<class T>
static void read(Decoder* d, std::vector<T>& v) {
  read(d, &v);
}

} // namespace marshal

} // namespace rtm

#endif /* MARSHAL_H_ */
