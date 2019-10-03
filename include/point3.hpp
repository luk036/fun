// The template and inlines for the -*- C++ -*- 3d point classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/point3.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_POINT3_HPP
#define FUN_POINT3_HPP 1

#include "vector3.hpp"

namespace fun {
/**
 * @defgroup 3d_point 3d Point in projective geometry
 * @ingroup geometry
 *
 * Classes and functions for 3d point.
 * @{
 */

// Forward declarations.
template <typename _K> class point3;
template <typename _K> class line3;
template <typename _K> struct point2;

/**
 *  Projective point: one dimensional subspace of K^3
 *
 *  @param  _K  Type of point elements
 */
template <typename _K = int> class point3 : public vector3<_K> {
  /// Value typedef.
  typedef _K value_type;
  typedef vector3<_K> _Base;

public:
  /// Default constructor.
  ///  Unspecified parameters default to 0.
  constexpr point3(const _K &x = _K(), const _K &y = _K(),
                   const _K &z = _K(1)) noexcept
      : _Base{x, y, z} {}

  /// Contruct from an affine point @a p.
  constexpr point3(const point2<_K> &p) noexcept : _Base{p.x(), p.y(), _K(1)} {}

  /// Construct from the base class
  constexpr point3(const vector3<_K> &v) noexcept : _Base{v} {}

  // Lets the compiler synthesize the copy constructor
  // point3 (const point3<_K>&);
  /// Copy constructor
  template <typename _Up>
  constexpr point3(const point3<_Up> &q) noexcept : _Base{q} {}

  /// Return the base class.
  constexpr vector3<_K> base() const noexcept { return *this; }

  /// Construct by meet of two lines @a l and @a m. (p. 53)
  constexpr point3(const line3<_K> &l, const line3<_K> &m) noexcept
      : _Base{cross(l, m)} {}

  /// Return first element of point.
  constexpr _K x() const noexcept { return _Base::e1(); }

  /// Return second element of point.
  constexpr _K y() const noexcept { return _Base::e2(); }

  /// Return third element of point.
  constexpr _K z() const noexcept { return _Base::e3(); }

  // Lets the compiler synthesize the assignment operator
  // point3<_K>& operator= (const point3<_K>&);
  /// Assign this point to point @a q.
  template <typename _Up> point3<_K> &operator=(const point3<_Up> &q) {
    *this = q;
    return *this;
  }

  /// Add @a v to this point.
  // xxx template<typename _Up>
  // xxx point3<_K>& operator+=(const vector3<_Up>& v)
  // xxx { this->base() += v; return *this; }
  // xxx
  // xxx /// Subtract @a v from this point.
  // xxx template<typename _Up>
  // xxx point3<_K>& operator-=(const vector3<_Up>& v)
  // xxx { this->base() -= v; return *this; }

  /// Return true if this point incident with a line @a l (p. 48)
  constexpr bool incident(const line3<_K> &l) const { return dot(*this, l) == _K(0); }
};

// Operators:
/// Return true if @a p is equal to @a q (in 3d affine sense).
template <typename _K>
inline constexpr bool operator==(const point3<_K> &p,
                                 const point3<_K> &q) noexcept {
  return p.x() == q.x() && p.y() == q.y() && p.z() == q.z();
}

/// Return true if @a p is equivalent to @a q (in projective sense).
template <typename _K>
inline constexpr bool equiv(const point3<_K> &p, const point3<_K> &q) noexcept {
  return p.x() * q.z() == p.z() * q.x() && p.y() * q.z() == p.z() * q.y();
}

/// Return false if @a p is equal to @a q.
template <typename _K>
inline constexpr bool operator!=(const point3<_K> &p,
                                 const point3<_K> &q) noexcept {
  return !(p == q);
}

///  Return new point @a p plus @a v.
// xxx template<typename _K>
// xxx   inline point3<_K>
// xxx   operator+(const point3<_K>& p, const vector3<_K>& v)
// xxx   {
// xxx     point3<_K> r = p;
// xxx     r += v;
// xxx     return r;
// xxx   }
// xxx
// xxx ///  Return new point @a p minus @a v.
// xxx template<typename _K>
// xxx   inline point3<_K>
// xxx   operator-(const point3<_K>& p, const vector3<_K>& v)
// xxx   {
// xxx     point3<_K> r = p;
// xxx     r -= v;
// xxx     return r;
// xxx   }
// xxx
// xxx ///  Return new vector @a p minus @a q.
// xxx template<typename _K>
// xxx   inline vector3<_K>
// xxx   operator-(const point3<_K>& p, const point3<_K>& q)
// xxx   {
// xxx     return p.base() - q.base();
// xxx   }

///  Return new line join @a p and @a q (p. 53)
template <typename _K>
inline constexpr line3<_K> join(const point3<_K> &p,
                                const point3<_K> &q) noexcept {
  return cross(p, q);
}

///  Return true if @a a V ( @a b, @a c, @a d, @a e) are harmonic (p. 102)
template <typename _K>
inline bool harmonic(const point3<_K> &a, const point3<_K> &b,
                     const point3<_K> &c, const point3<_K> &d,
                     const point3<_K> &e) {
  auto ab = cross(a, b);
  auto ac = cross(a, c);
  return dot(ab, d) * dot(ac, e) == -dot(ab, e) * dot(ac, d);
}

///  Return true if @a a, @a b, @a c, @a d, @a e, @a f are on a conic  (p. 102)
template <class _Point3>
inline bool on_a_conic(const _Point3 &a, const _Point3 &b, const _Point3 &c,
                       const _Point3 &d, const _Point3 &e, const _Point3 &f) {
  auto bc = cross(b, c);
  auto ef = cross(e, f);
  auto bf = cross(b, f);
  auto ec = cross(e, c);
  return dot(a, bc) * dot(a, ef) * dot(d, bf) * dot(d, ec) ==
         dot(d, ef) * dot(d, bc) * dot(a, ec) * dot(a, bf);
}

///  Insertion operator for point values.
template <typename _Point3, class _Stream>
_Stream &operator<<(_Stream &os, const _Point3 &p) {
  os << '[' << p.x() << ':' << p.y() << ':' << p.z() << ']';
  return os;
}
}

#endif
