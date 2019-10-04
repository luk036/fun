// The template and inlines for the -*- C++ -*- 3d point classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/pg_point.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_PG_POINT_HPP
#define FUN_PG_POINT_HPP 1

#include "pg_line.hpp"
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
template <typename _K> class pg_line;

/**
 *  Projective point: one dimensional subspace of K^3
 *
 *  @param  _K  Type of point elements
 */
template <typename _K = int> class pg_point : public vector3d<_K> {
  /// Value typedef.
  typedef _K value_type;
  typedef vector3d<_K> _Base;

public:
  typedef pg_line<_K> dual;

  /// Default constructor.
  constexpr pg_point(const _K &x = _K(0), const _K &y = _K(0),
                     const _K &z = _K(1)) noexcept
      : _Base{x, y, z} {}

  /// Construct from base class.
  constexpr pg_point(_Base v) noexcept : _Base{v} {}

  // Lets the compiler synthesize the copy constructor
  // pg_point (const pg_point<_K>&);
  /// Return the base class.
  constexpr vector3d<_K> base() noexcept { return *this; }

  /// Construct by meet of two lines @a l and @a m. (p. 53)
  constexpr pg_point(const pg_line<_K> &l, const pg_line<_K> &m) noexcept
      : _Base{cross(l, m)} {}

  /// Return first element of point.
  constexpr _K x() const noexcept { return _Base::e1(); }
  /// Return second element of point.
  constexpr _K y() const noexcept { return _Base::e2(); }
  /// Return third element of point.
  constexpr _K z() const noexcept { return _Base::e3(); }
};

// Operators:

/// Return true if @a p is equivalent to @a q (in projective sense).
template <typename _K>
inline constexpr bool operator==(const pg_point<_K> &p,
                                 const pg_point<_K> &q) noexcept {
  return cross(p, q) == vector3d<_K>::zero;
}

///  Return new line join @a p and @a q (p. 53)
template <typename _K>
inline constexpr pg_line<_K> join(const pg_point<_K> &p,
                                  const pg_point<_K> &q) noexcept {
  return cross(p, q);
}

/// Return true if a line @a l incident with point @a p
template <typename _K>
inline bool I(const pg_point<_K> &p, const pg_line<_K> &l) noexcept {
  return dot(p, l) == _K(0);
}

///  Return new line join @a p and @a q (p. 53)
template <typename _K>
inline constexpr pg_point<_K> aux1(const pg_point<_K> &p,
                                   const pg_point<_K> &q) noexcept {
  return pg_point<_K>{p + q};
}

///  Return new line join @a p and @a q (p. 53)
template <typename _K>
inline constexpr pg_line<_K> aux2(const pg_point<_K> &p) noexcept {
  return pg_line<_K>{p};
}

///  Insertion operator for point values.
template <typename _Point3d, class _Stream>
_Stream &operator<<(_Stream &os, const _Point3d &p) {
  os << '(' << p.x() << ':' << p.y() << ':' << p.z() << ')';
  return os;
}
}

#endif
