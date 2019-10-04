// The template and inlines for the -*- C++ -*- 3d point classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/point3d.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_POINT3D_HPP
#define FUN_POINT3D_HPP 1

#include "line3d.hpp"
#include "vector3d.hpp"

namespace fun {
/**
 * @defgroup 3d_point 3d Point in projective geometry
 * @ingroup geometry
 *
 * Classes and functions for 3d point.
 * @{
 */

// Forward declarations.
template <typename _K> class point3d;
template <typename _K> class line3d;
template <typename _K> struct point2d;

/**
 *  Projective point: one dimensional subspace of K^3
 *
 *  @param  _K  Type of point elements
 */
template <typename _K = int> class point3d : public vector3d<_K> {
  /// Value typedef.
  typedef _K value_type;
  typedef vector3d<_K> _Base;

public:
  typedef line3d<_K> dual;

  /// Default constructor.
  ///  Unspecified parameters default to 0.
  constexpr point3d(const _K &x = _K(0), const _K &y = _K(0),
                    const _K &z = _K(1)) noexcept
      : _Base{x, y, z} {}

  /// Contruct from an affine point @a p.
  constexpr point3d(const point2d<_K> &p) noexcept
      : _Base{p.x(), p.y(), _K(1)} {}

  /// Construct from the base class
  constexpr point3d(const vector3d<_K> &v) noexcept : _Base{v} {}

  // Lets the compiler synthesize the copy constructor
  // point3d (const point3d<_K>&);
  /// Copy constructor
  template <typename _Up>
  constexpr point3d(const point3d<_Up> &q) noexcept : _Base{q} {}

  /// Return the base class.
  constexpr vector3d<_K> base() const noexcept { return *this; }

  /// Construct by meet of two lines @a l and @a m. (p. 53)
  constexpr point3d(const line3d<_K> &l, const line3d<_K> &m) noexcept
      : _Base{cross(l, m)} {}

  /// Return first element of point.
  constexpr _K x() const noexcept { return _Base::e1(); }

  /// Return second element of point.
  constexpr _K y() const noexcept { return _Base::e2(); }

  /// Return third element of point.
  constexpr _K z() const noexcept { return _Base::e3(); }

  bool incident(const line3d<_K> &l) const noexcept {
    return dot(*this, l) == _K(0);
  }

  // Lets the compiler synthesize the assignment operator
  // point3d<_K>& operator= (const point3d<_K>&);
  /// Assign this point to point @a q.
  template <typename _Up> point3d<_K> &operator=(const point3d<_Up> &q) {
    *this = q;
    return *this;
  }
};

// Operators:

/// Return true if @a p is equivalent to @a q (in projective sense).
template <typename _K>
inline constexpr bool operator==(const point3d<_K> &p,
                                 const point3d<_K> &q) noexcept {
  return cross(p, q) == vector3d<_K>::zero;
}

/// Return false if @a p is equal to @a q.
template <typename _K>
inline constexpr bool operator!=(const point3d<_K> &p,
                                 const point3d<_K> &q) noexcept {
  return !(p == q);
}

///  Return new point @a p plus @a v.
// xxx template<typename _K>
// xxx   inline point3d<_K>
// xxx   operator+(const point3d<_K>& p, const vector3d<_K>& v)
// xxx   {
// xxx     point3d<_K> r = p;
// xxx     r += v;
// xxx     return r;
// xxx   }
// xxx
// xxx ///  Return new point @a p minus @a v.
// xxx template<typename _K>
// xxx   inline point3d<_K>
// xxx   operator-(const point3d<_K>& p, const vector3d<_K>& v)
// xxx   {
// xxx     point3d<_K> r = p;
// xxx     r -= v;
// xxx     return r;
// xxx   }
// xxx
// xxx ///  Return new vector @a p minus @a q.
// xxx template<typename _K>
// xxx   inline vector3d<_K>
// xxx   operator-(const point3d<_K>& p, const point3d<_K>& q)
// xxx   {
// xxx     return p.base() - q.base();
// xxx   }

///  Return new line join @a p and @a q (p. 53)
template <typename _K>
inline constexpr line3d<_K> join(const point3d<_K> &p,
                                 const point3d<_K> &q) noexcept {
  return cross(p, q);
}

template <typename _K>
inline constexpr line3d<_K> operator*(const point3d<_K> &p,
                                      const point3d<_K> &q) noexcept {
  return cross(p, q);
}

/// Return true if a line @a l incident with point @a p
template <typename _K>
inline bool incident(const point3d<_K> &p, const line3d<_K> &l) noexcept {
  return dot(p, l) == _K(0);
}

/// Return true if a line @a l incident with point @a p
template <typename _K>
inline bool I(const point3d<_K> &p, const line3d<_K> &l) noexcept {
  return dot(p, l) == _K(0);
}

///  Return an auxiliary point of @a p and @a q
template <typename _K>
inline constexpr point3d<_K> auxiliary(const point3d<_K> &p,
                                       const point3d<_K> &q) noexcept {
  return cross(p, q);
}

///  Return true if @a a V ( @a b, @a c, @a d, @a e) are harmonic (p. 102)
template <typename _K>
inline bool harmonic(const point3d<_K> &a, const point3d<_K> &b,
                     const point3d<_K> &c, const point3d<_K> &d,
                     const point3d<_K> &e) {
  auto ab = cross(a, b);
  auto ac = cross(a, c);
  return dot(ab, d) * dot(ac, e) == -dot(ab, e) * dot(ac, d);
}

///  Return true if @a a, @a b, @a c, @a d, @a e, @a f are on a conic  (p. 102)
template <class _Point3d>
inline bool on_a_conic(const _Point3d &a, const _Point3d &b, const _Point3d &c,
                       const _Point3d &d, const _Point3d &e,
                       const _Point3d &f) {
  // xxx auto bc = cross(b,c); auto ef = cross(e,f);
  // xxx auto bf = cross(b,f); auto ec = cross(e,c);
  // xxx return dot(a,bc)*dot(a,ef)*dot(d,bf)*dot(d,ec)
  // xxx   == dot(d,ef)*dot(d,bc)*dot(a,ec)*dot(a,bf);
  return on_a_conic_T(a, cross(b, c), cross(e, f), d, cross(b, f), cross(e, c));
}

///  Return true if @a a, @a b, @a c, @a d, @a e, @a f are on a conic  (p. 102)
template <class _Point3d, class Auto>
inline bool on_a_conic_T(const _Point3d &a, const Auto &bc, const Auto &ef,
                         const _Point3d &d, const Auto &bf, const Auto &ec) {
  // auto bc = cross(b,c); auto ef = cross(e,f);
  // auto bf = cross(b,f); auto ec = cross(e,c);
  return dot(a, bc) * dot(a, ef) * dot(d, bf) * dot(d, ec) ==
         dot(d, ef) * dot(d, bc) * dot(a, ec) * dot(a, bf);
}

///  Insertion operator for point values.
template <typename _Point3d, class _Stream>
_Stream &operator<<(_Stream &os, const _Point3d &p) {
  os << '[' << p.x() << ':' << p.y() << ':' << p.z() << ']';
  return os;
}
}

#endif
