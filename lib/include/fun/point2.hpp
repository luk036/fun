// The template and inlines for the -*- C++ -*- 2d point classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/point2.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_POINT2_HPP
#define FUN_POINT2_HPP 1

#include "vector2d.hpp"

namespace fun {
/**
 * @defgroup 2d_point 2d Point
 * @ingroup geometry
 *
 * Classes and functions for 2d point.
 * @{
 */

// Forward declarations.
template <typename _K> struct point2;
template <typename _K> class line3;

/**
 *  2-dimensional point.
 *
 *  @param  Tp  Type of point elements
 */
template <typename _K> struct point2 {
  /// Value typedef.
  typedef _K value_type;

  /// Default constructor.
  ///  Unspecified parameters default to 0.
  constexpr point2(const _K &x = _K(), const _K &y = _K()) noexcept
      : _x{x}, _y{y} {}

  // Lets the compiler synthesize the copy constructor
  // point2 (const point2<_K>&);
  /// Copy constructor
  template <typename _Up>
  constexpr point2(const point2<_Up> &q) noexcept : _x{q.x()}, _y{q.y()} {}

  /// Return first element of point.
  constexpr _K x() noexcept { return _x; }

  /// Return second element of point.
  constexpr _K y() noexcept { return _y; }

  // Lets the compiler synthesize the assignment operator
  // point2<_K>& operator= (const point2<_K>&);
  /// Assign this point to point @a q.
  template <typename _Up> point2<_K> &operator=(const point2<_Up> &q) {
    _x = q.x();
    _y = q.y();
    return *this;
  }

  /// Add @a v to this point.
  template <typename _Up> point2<_K> &operator+=(const vector2d<_Up> &v) {
    _x += v.e1();
    _y += v.e2();
    return *this;
  }

  /// Subtract @a v from this point.
  template <typename _Up> point2<_K> &operator-=(const vector2d<_Up> &v) {
    _x -= v.e1();
    _y -= v.e2();
    return *this;
  }

private:
  _K _x;
  _K _y;
};

// Operators:
///  Return new point @a p plus @a v.
template <typename _K>
inline point2<_K> operator+(point2<_K> p, const vector2d<_K> &v) {
  return p += v;
}

///  Return new point @a p minus @a v.
template <typename _K>
inline point2<_K> operator-(point2<_K> p, const vector2d<_K> &v) {
  return p -= v;
}

///  Return new vector @a p minus @a q.
template <typename _K>
inline constexpr vector2d<_K> operator-(const point2<_K> &p,
                                        const point2<_K> &q) noexcept {
  return vector2d<_K>(p.x() - q.x(), p.y() - q.y());
}

/// Return negation of @a p
template <typename _K>
inline constexpr point2<_K> operator-(const point2<_K> &p) noexcept {
  return point2<_K>(-p.x(), -p.y());
}

/// Return true if @a p is equal to @a q.
template <typename _K>
inline constexpr bool operator==(const point2<_K> &p,
                                 const point2<_K> &q) noexcept {
  return p.x() == q.x() && p.y() == q.y();
}

/// Return false if @a p is equal to @a q.
template <typename _K>
inline constexpr bool operator!=(const point2<_K> &p,
                                 const point2<_K> &q) noexcept {
  return p.x() != q.x() || p.y() != q.y();
}

///  Return new line join @a p and @a q (p. 53)
template <typename _K>
inline constexpr line3<_K> join(const point2<_K> &p,
                                const point2<_K> &q) noexcept {
  return line3<_K>(p.y() - q.y(), -p.x() + q.x(),
                   p.x() * q.y() - p.y() * q.x());
}

///  Return true if @a a, @a b, @a c are collinear
template <typename _K>
inline constexpr bool collinear(const point2<_K> &a, const point2<_K> &b,
                                const point2<_K> &c) noexcept {
  return det(a - c, b - c) == _K(0);
}

///  Return true if @a a, @a b, @a c, @a d, @a e, @a f are on a conic
template <typename _K>
inline bool on_a_conic(const point2<_K> &a, const point2<_K> &b,
                       const point2<_K> &c, const point2<_K> &d,
                       const point2<_K> &e, const point2<_K> &f) {
  auto ca = a - c;
  auto fa = a - f;
  auto cb = b - c;
  auto fb = b - f;
  auto cd = d - c;
  auto fd = d - f;
  auto ce = e - c;
  auto fe = e - f;
  return det(ca, cb) * det(fa, fe) * det(fd, fb) * det(cd, ce) ==
         det(fd, fe) * det(cd, cb) * det(ca, ce) * det(fa, fb);
}

///  Return true if @a a, @a b, @a c, @a d are on a circle
template <typename _K>
inline bool on_a_circle(const point2<_K> &a, const point2<_K> &b,
                        const point2<_K> &c, const point2<_K> &d) {
  auto ca = a - c;
  auto da = a - d;
  auto cb = b - c;
  auto db = b - d;
  return det(da, db) * dot(ca, cb) == dot(da, db) * det(ca, cb);
}

///  Return positive if @a S are outside a circle containing @a P @a Q
///  and @a R. Return 0 if it is on the circle.
template <typename _K>
inline _K outside_circle(const point2<_K> &P, const point2<_K> &Q,
                         const point2<_K> &R, const point2<_K> &S) {
  auto PR = R - P;
  auto QR = R - Q;
  auto PS = S - P;
  auto QS = S - Q;
  auto LPQR = det(PR, QR);
  auto res = LPQR * dot(PS, QS) - dot(PR, QR) * det(PS, QS);
  if (LPQR < _K(0))
    res = -res;
  return res;
}

///  Insertion operator for point values.
template <typename _K, class _Stream>
_Stream &operator<<(_Stream &os, const point2<_K> &p) {
  os << '[' << p.x() << ',' << p.y() << ']';
  return os;
}
}

#endif
