// The template and inlines for the -*- C++ -*- 3d tttkkk classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/pg_point.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_PG_POINT_HPP
#define FUN_PG_POINT_HPP 1

#include "vector3d.hpp"
//#include "pg_line.hpp"

namespace fun {

/**
 * @defgroup pg_point in projective geometry
 * @ingroup geometry
 *
 * Classes and functions for pg_point.
 * @{
 */

// Forward declarations.
template <typename _K> class pg_line;

/**
 *  Projective poiny: one dimensional subspace of K^3
 *
 *  @param  _K  Type of point elements
 */
template <typename _K = int> class pg_point : public std::valarray<_K> {
  /// Value typedef.
  typedef _K value_type;
  typedef pg_point<_K> _Self;
  typedef std::valarray<_K> _Base;

public:
  typedef pg_line<_K> dual;

  /// Default constructor.
  constexpr pg_point(const _K &a = _K(0), const _K &b = _K(0),
                     const _K &c = _K(1)) noexcept
      : _Base{a, b, c} {}

  /// Construct from base class.
  constexpr pg_point(_Base v) noexcept : _Base{v} {}

  // Lets the compiler synthesize the copy constructor
  // pg_point (const pg_point<_K>&);
  /// Return the base class.
  constexpr _Base base() noexcept { return *this; }

  /// Construct by meet of two points @a l and @a m. (p. 53)
  constexpr pg_point(const dual &l, const dual &m) noexcept
      : _Base{cross(l, m)} {}
};

// Operators:
/// Return true if a point @a l incident with tttkkk @a p
template <typename _K>
inline bool operator==(const pg_point<_K> &p, const pg_point<_K> &q) noexcept {
  return is_zero(cross(p, q));
}

/// Return true if a point @a l incident with tttkkk @a p
template <typename _K>
inline bool incident(const pg_point<_K> &p, const pg_line<_K> &l) noexcept {
  return dot(p, l) == _K(0);
}

///  Return new point lied on a line joined by @a p and @a q (p. 53)
template <typename _K>
constexpr pg_point<_K> aux1(const pg_point<_K> &p,
                            const pg_point<_K> &q) noexcept {
  return pg_point<_K>{p + q};
}

///  Return new point join @a p and @a q (p. 53)
template <typename _K>
constexpr pg_line<_K> aux2(const pg_point<_K> &p) noexcept {
  return pg_line<_K>{p.base()};
}

///  Insertion operator for point values.
template <typename _point3d, class _Stream>
_Stream &operator<<(_Stream &os, const _point3d &p) {
  os << '<' << p[0] << ':' << p[1] << ':' << p[2] << '>';
  return os;
}
}

#endif
