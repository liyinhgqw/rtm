#ifndef UTIL_TUPLE_H_
#define UTIL_TUPLE_H_

#include <boost/tuple/tuple.hpp>

namespace rtm {

class Tuple {
public:
  static boost::tuple<> create() {
    return boost::make_tuple();
  }

  template<class T0>
  static boost::tuple<T0> create(const T0& v_0) {
    return boost::make_tuple(v_0);
  }
  template<class T0, class T1>
  static boost::tuple<T0, T1> create(const T0& v_0, const T1& v_1) {
    return boost::make_tuple(v_0, v_1);
  }
  template<class T0, class T1, class T2>
  static boost::tuple<T0, T1, T2> create(const T0& v_0, const T1& v_1,
      const T2& v_2) {
    return boost::make_tuple(v_0, v_1, v_2);
  }
  template<class T0, class T1, class T2, class T3>
  static boost::tuple<T0, T1, T2, T3> create(const T0& v_0, const T1& v_1,
      const T2& v_2, const T3& v_3) {
    return boost::make_tuple(v_0, v_1, v_2, v_3);
  }
  template<class T0, class T1, class T2, class T3, class T4>
  static boost::tuple<T0, T1, T2, T3, T4> create(const T0& v_0, const T1& v_1,
      const T2& v_2, const T3& v_3, const T4& v_4) {
    return boost::make_tuple(v_0, v_1, v_2, v_3, v_4);
  }
  template<class T0, class T1, class T2, class T3, class T4, class T5>
  static boost::tuple<T0, T1, T2, T3, T4, T5> create(const T0& v_0,
      const T1& v_1, const T2& v_2, const T3& v_3, const T4& v_4,
      const T5& v_5) {
    return boost::make_tuple(v_0, v_1, v_2, v_3, v_4, v_5);
  }
  template<class T0, class T1, class T2, class T3, class T4, class T5, class T6>
  static boost::tuple<T0, T1, T2, T3, T4, T5, T6> create(const T0& v_0,
      const T1& v_1, const T2& v_2, const T3& v_3, const T4& v_4, const T5& v_5,
      const T6& v_6) {
    return boost::make_tuple(v_0, v_1, v_2, v_3, v_4, v_5, v_6);
  }
  template<class T0, class T1, class T2, class T3, class T4, class T5, class T6,
      class T7>
  static boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> create(const T0& v_0,
      const T1& v_1, const T2& v_2, const T3& v_3, const T4& v_4, const T5& v_5,
      const T6& v_6, const T7& v_7) {
    return boost::make_tuple(v_0, v_1, v_2, v_3, v_4, v_5, v_6, v_7);
  }
};

}  // namespace rtm

#endif /* UTIL_TUPLE_H_ */
