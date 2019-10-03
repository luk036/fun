// The template and inlines for the -*- C++ -*- 3d line classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/line3d.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_LINE3D_HPP
#define FUN_LINE3D_HPP 1

#include "point3d.hpp"
#include "vector3d.hpp"

namespace fun {
/**
 * @defgroup 3d_line 3d Line in projective geometry
 * @ingroup geometry
 *
 * Classes and functions for 3d line.
 * @{
 */

// Forward declarations.
template <typename _K> class point3d;
template <typename _K> class line3d;
// xxx template<typename _K> class rational;

/**
 *  Projective line represented by homogenous coordinates.
 *
 *  @param  Tp  Type of line elements
 */
template <typename _K = int> class line3d : public vector3d<_K> {
  /// Value typedef.
  typedef _K value_type;
  typedef vector3d<_K> _Base;

public:
  typedef point3d<_K> dual;

  /// Default constructor.
  ///  Unspecified parameters default to 0 (line at Infinity).
  constexpr line3d(const _K &x = _K(0), const _K &y = _K(0),
                   const _K &z = _K(1)) noexcept
      : _Base{x, y, z} {}

  /// Construct from the base class @a v
  constexpr line3d(const vector3d<_K> &v) noexcept : _Base{v} {}

  // Lets the compiler synthesize the copy constructor
  // line3d (const line3d<_K>&);
  /// Copy constructor
  template <typename _Up>
  constexpr line3d(const line3d<_Up> &q) noexcept : _Base{q} {}

  /// Return the base class
  constexpr vector3d<_K> base() const noexcept { return *this; }

  /// Construct by join of two points @a p and @a q (p. 53)
  constexpr line3d(const point3d<_K> &p, const point3d<_K> &q) noexcept
      : _Base{cross(p, q)} {}

  /// Return first element of line.
  constexpr _K a() const noexcept { return _Base::e1(); }

  /// Return second element of line.
  constexpr _K b() const noexcept { return _Base::e2(); }

  /// Return third element of line.
  constexpr _K c() const noexcept { return _Base::e3(); }

  /// Return true if a point @a p incident with line @a l
  bool incident(const point3d<_K> &p) const noexcept {
    return dot(p, *this) == _K(0);
  }

  // Lets the compiler synthesize the assignment operator
  // line3d<_K>& operator= (const line3d<_K>&);
};

// Operators:

/// Return true if @a p is equivalent to @a q (in projective sense).
template <typename _K>
inline constexpr bool operator==(const line3d<_K> &l,
                                 const line3d<_K> &m) noexcept {
  return cross(l, m) == vector3d<_K>::zero;
}

/// Return false if @a p is equal to @a q.
template <typename _K>
inline constexpr bool operator!=(const line3d<_K> &l,
                                 const line3d<_K> &m) noexcept {
  return !(l == m);
}

///  Return new point meet @a l and @a m (p. 53)
template <typename _K>
inline constexpr point3d<_K> meet(const line3d<_K> &l,
                                  const line3d<_K> &m) noexcept {
  return cross(l, m);
}

///  Return new point meet @a l and @a m (p. 53)
template <typename _K>
inline constexpr point3d<_K> operator*(const line3d<_K> &l,
                                       const line3d<_K> &m) noexcept {
  return cross(l, m);
}

/// Return incident of @a l and @a p
template <typename _K>
inline bool I(const line3d<_K> &l, const point3d<_K> &p) {
  return l.incident(p);
}

/// Return incident of @a l and @a p
template <typename _K>
inline bool incident(const line3d<_K> &l, const point3d<_K> &p) {
  return l.incident(p);
}

/// Return true if a point @a p incident with line @a l
// xxx template <typename _K>
// xxx inline bool
// xxx incident(const point3d<_K>& p, const line3d<_K>& l) noexcept
// xxx { return dot(p, l) == _K(0); }

///  Return an auxiliary line of @a l and @a m
template <typename _K>
inline constexpr line3d<_K> auxiliary(const line3d<_K> &l,
                                      const line3d<_K> &m) noexcept {
  return cross(l, m);
}

///  Insertion operator for line values.
template <typename _K, class _Stream>
_Stream &operator<<(_Stream &os, const line3d<_K> &l) {
  os << '<' << l.a() << ':' << l.b() << ':' << l.c() << '>';
  return os;
}
} // namespace fun

#endif
