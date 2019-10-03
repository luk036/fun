#ifndef MAX_PLUS_HPP
#define MAX_PLUS_HPP 1

/* http://melpon.org/wandbox/permlink/paCC61fxm2muS5lc */

#include <cmath>

namespace fun {

template <typename T> class maxPlus {
public:
  using Self = maxPlus<T>;
  maxPlus() : _val{-1000} {};
  maxPlus(const T &val) : _val{val} {}
  operator T &() { return _val; }
  operator T() const { return _val; }
  T &val() { return _val; }
  T val() const { return _val; }
  Self &operator+=(const Self &rhs) { // max
    if (val() < rhs.val())
      _val = rhs.val();
    return *this;
  }
  Self &operator*=(const Self &rhs) { // plus
    _val += rhs.val();
    return *this;
  }

private:
  T _val;
};

template <typename T>
maxPlus<T> operator+(maxPlus<T> lhs, const maxPlus<T> &rhs) { // max
  return lhs += rhs;
}

template <typename T>
maxPlus<T> operator*(maxPlus<T> lhs, const maxPlus<T> &rhs) { // max
  return lhs *= rhs;
}

} // namespace

#endif
