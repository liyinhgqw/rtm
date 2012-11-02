#ifndef LISTUTIL_H_
#define LISTUTIL_H_

#include <boost/tuple/tuple.hpp>
#include <vector>

namespace rtm {

template<class T>
std::vector<T> make_list() {
  std::vector<T> res;
  return res;
}

template<class T>
std::vector<T> make_list(const T& arg0) {
  std::vector<T> res;
  res.push(arg0);
  return res;
}

template<class T>
std::vector<T> make_list(const T& arg0, const T& arg1) {
  std::vector<T> res;
  res.push(arg0);
  res.push(arg1);
  return res;
}

template<class T>
std::vector<T> make_list(const T& arg0, const T& arg1, const T& arg2) {
  std::vector<T> res;
  res.push(arg0);
  res.push(arg1);
  res.push(arg2);
  return res;
}

template<class T>
std::vector<T> make_list(const T& arg0, const T& arg1, const T& arg2, const T& arg3) {
  std::vector<T> res;
  res.push(arg0);
  res.push(arg1);
  res.push(arg2);
  res.push(arg3);
  return res;
}

template<class T>
std::vector<T> make_list(const T& arg0, const T& arg1, const T& arg2, const T& arg3,
    const T& arg4) {
  std::vector<T> res;
  res.push(arg0);
  res.push(arg1);
  res.push(arg2);
  res.push(arg3);
  res.push(arg4);
  return res;
}

template<class T>
std::vector<T> make_list(const T& arg0, const T& arg1, const T& arg2, const T& arg3,
    const T& arg4, const T& arg5) {
  std::vector<T> res;
  res.push(arg0);
  res.push(arg1);
  res.push(arg2);
  res.push(arg3);
  res.push(arg4);
  res.push(arg5);
  return res;
}

template<class T>
std::vector<T> make_list(const T& arg0, const T& arg1, const T& arg2, const T& arg3,
    const T& arg4, const T& arg5, const T& arg6) {
  std::vector<T> res;
  res.push(arg0);
  res.push(arg1);
  res.push(arg2);
  res.push(arg3);
  res.push(arg4);
  res.push(arg5);
  res.push(arg6);
  return res;
}

template<class T>
std::vector<T> make_list(const T& arg0, const T& arg1, const T& arg2, const T& arg3,
    const T& arg4, const T& arg5, const T& arg6, const T& arg7) {
  std::vector<T> res;
  res.push(arg0);
  res.push(arg1);
  res.push(arg2);
  res.push(arg3);
  res.push(arg4);
  res.push(arg5);
  res.push(arg6);
  res.push(arg7);
  return res;
}

template<class T>
std::vector<T> make_list(const T& arg0, const T& arg1, const T& arg2, const T& arg3,
    const T& arg4, const T& arg5, const T& arg6, const T& arg7, const T& arg8) {
  std::vector<T> res;
  res.push(arg0);
  res.push(arg1);
  res.push(arg2);
  res.push(arg3);
  res.push(arg4);
  res.push(arg5);
  res.push(arg6);
  res.push(arg7);
  res.push(arg8);
  return res;
}

} // namespace rtm
#endif /* LISTUTIL_H_ */
