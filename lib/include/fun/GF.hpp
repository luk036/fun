// The template and inlines for the -*- C++ -*- finite field classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/GF.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_GF_HPP
#define FUN_GF_HPP 1

#include <boost/operators.hpp>
#include <cassert>

namespace fun {
/**
 * @defgroup GF Finite (Galois) Field
 * @ingroup arithmetic
 *
 * Classes and functions for (extended) finite field.
 * @{
 */

// Forward declarations.
template <unsigned int _p> struct GF;

/**
 *  finite (Galois) field.
 *
 *  @param  p  Prime number
 */
template <unsigned int _p = 3> struct GF : boost::field_operators<GF<_p>> {
  /// Default constructor.
  constexpr GF() noexcept : _m(0) {}

  ///  Unspecified parameters default to 0.
  explicit GF(unsigned int m) noexcept : _m(m) { assert(_m < _p); }

  // Lets the compiler synthesize the copy constructor
  // GF (const GF<_p>&);
  /// Copy constructor
  GF(const GF<_p> &s) noexcept : _m(s.value()) { assert(_m >= 0); }

  /// Return internal element of finite field.
  constexpr unsigned int value() const noexcept { return _m; }

  // Lets the compiler synthesize the assignment operator
  // GF<_p>& operator= (const GF<_p>&);
  /// Assign this finite field to finite field @a s.
  GF<_p> &operator=(const GF<_p> &s) {
    _m = s.value();
    return *this;
  }

  /// Add @a s to this finite field.
  GF<_p> &operator+=(const GF<_p> &s) {
    _m += s.value();
    _m %= _p;
    assert(_m < _p);
    return *this;
  }

  /// Subtract @a s from this finite field.
  GF<_p> &operator-=(const GF<_p> &s) {
    _m += _p - s.value();
    _m = _m % _p;
    assert(_m < _p);
    return *this;
  }

  /// Multiply @a s to this finite field.
  GF<_p> &operator*=(const GF<_p> &s) {
    _m *= s.value();
    _m %= _p;
    assert(_m < _p);
    return *this;
  }

private:
  unsigned int _m;
};

// Operators:
///  Return new finite field @a r plus @a s.
template <unsigned int _p> inline GF<_p> operator+(GF<_p> r, const GF<_p> &s) {
  return r += s;
}

///  Return new finite field @a r minus @a s.
template <unsigned int _p> inline GF<_p> operator-(GF<_p> r, const GF<_p> &s) {
  return r -= s;
}

//@{
///  Return new finite field @a r times @a a.
template <unsigned int _p> inline GF<_p> operator*(GF<_p> r, const GF<_p> &s) {
  return r *= s;
}
//@}

/// Return @a r.
template <unsigned int _p>
inline constexpr GF<_p> operator+(const GF<_p> &r) noexcept {
  return r;
}

/// Return negation of @a r
template <unsigned int _p> inline GF<_p> operator-(const GF<_p> &r) {
  if (r.value() == 0)
    return r;
  return GF<_p>(_p - r.value());
}

/// Return true if @a r is equal to @a s.
template <unsigned int _p>
inline constexpr bool operator==(const GF<_p> &r, const GF<_p> &s) noexcept {
  return r.value() == s.value();
}

/// Return false if @a r is equal to @a s.
template <unsigned int _p>
inline constexpr bool operator!=(const GF<_p> &r, const GF<_p> &s) noexcept {
  return !(r == s);
}

///  Insertion operator for finite field values.
template <unsigned int _p, class _Stream>
_Stream &operator<<(_Stream &os, const GF<_p> &r) {
  os << '(' << r.value() << " mod " << _p << ')';
  return os;
}
}

#endif
