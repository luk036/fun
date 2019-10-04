// The template and inlines for the -*- C++ -*- 3d line classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/line3.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_LINE3_HPP
#define FUN_LINE3_HPP 1

#include "vector3.hpp"

namespace fun {
/**
 * @defgroup 3d_line 3d Line in projective geometry
 * @ingroup geometry
 *
 * Classes and functions for 3d line.
 * @{
 */

// Forward declarations.
template <typename _K> class point3;
template <typename _K> class line3;
template <typename _K> struct point2;
// xxx template<typename _K> class rational;

/**
 *  Projective line represented by homogenous coordinates.
 *
 *  @param  Tp  Type of line elements
 */
template <typename _K = int> class line3 : public vector3<_K> {
  /// Value typedef.
  typedef _K value_type;
  typedef vector3<_K> _Base;

public:
  typedef point3<_K> dual;

  /// Default constructor.
  ///  Unspecified parameters default to 0 (line at Infinity).
  constexpr line3(const _K &x = _K(0), const _K &y = _K(0),
                  const _K &z = _K(1)) noexcept
      : _Base{x, y, z} {}

  /// Construct from the base class @a v
  constexpr line3(const vector3<_K> &v) noexcept : _Base{v} {}

  // Lets the compiler synthesize the copy constructor
  // line3 (const line3<_K>&);
  /// Copy constructor
  template <typename _Up>
  constexpr line3(const line3<_Up> &q) noexcept : _Base{q} {}

  /// Return the base class
  constexpr vector3<_K> base() const noexcept { return *this; }

  /// Construct by join of two points @a p and @a q (p. 53)
  constexpr line3(const point3<_K> &p, const point3<_K> &q) noexcept
      : _Base{cross(p, q)} {}

  /// Return first element of line.
  constexpr _K a() const noexcept { return _Base::e1(); }

  /// Return second element of line.
  constexpr _K b() const noexcept { return _Base::e2(); }

  /// Return third element of line.
  constexpr _K c() const noexcept { return _Base::e3(); }

  // Lets the compiler synthesize the assignment operator
  // line3<_K>& operator= (const line3<_K>&);

  /// Return true if a point @a p incident with this line
  constexpr bool incident(const point3<_K> &p) const noexcept {
    return dot(p, *this) == _K(0);
  }
};

// Operators:
/// Return true if @a p is equal to @a q (in 3d affine sense).
template <typename _K>
inline constexpr bool operator==(const line3<_K> &l,
                                 const line3<_K> &m) noexcept {
  return l.a() == m.a() && l.b() == m.b() && l.c() == m.c();
}

/// Return true if @a p is equivalent to @a q (in projective sense).
template <typename _K>
inline constexpr bool equiv(const line3<_K> &l, const line3<_K> &m) noexcept {
  return l.a() * m.c() == l.c() * m.a() && l.b() * m.c() == l.c() * m.b();
}

/// Return false if @a p is equal to @a q.
template <typename _K>
inline constexpr bool operator!=(const line3<_K> &l,
                                 const line3<_K> &m) noexcept {
  return !(l == m);
}

///  Return new point meet @a l and @a m (p. 53)
template <typename _K>
inline constexpr point3<_K> meet(const line3<_K> &l,
                                 const line3<_K> &m) noexcept {
  return cross(l, m);
}

///  Insertion operator for line values.
template <typename _K, class _Stream>
_Stream &operator<<(_Stream &os, const line3<_K> &l) {
  os << '<' << l.a() << ':' << l.b() << ':' << l.c() << '>';
  return os;
}
} // namespace fun

#endif
