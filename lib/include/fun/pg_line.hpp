// The template and inlines for the -*- C++ -*- 3d line classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/pg_line.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_PG_LINE_HPP
#define FUN_PG_LINE_HPP 1

#include "vector3d.hpp"
#include "pg_point.hpp"
 
namespace fun 
{

/**
* @defgroup 3d_line 3d Line in projective geometry
* @ingroup geometry
*
* Classes and functions for 3d line.
* @{
*/

// Forward declarations.
template<typename _K> class pg_point;

/** 
 *  Projective line represented by homogenous coordinates. 
 *
 *  @param  Tp  Type of line elements
 */
template <typename _K = int>
class pg_line : public vector3d<_K>
{
  /// Value typedef.
  typedef _K value_type;
  typedef vector3d<_K> _Base;

public:
  typedef pg_point<_K> dual;

  /// Default constructor.
  ///  Unspecified parameters default to 0 (line at Infinity).
  constexpr pg_line(
      const _K& x = _K(0), 
      const _K& y = _K(0), 
      const _K& z = _K(1)) noexcept 
    : _Base{x, y, z} { }

  /// Construct from the base class @a v
  constexpr pg_line(const _Base& v) noexcept : _Base{v} { }

   /// Return the base class
  constexpr vector3d<_K> base() noexcept { return *this; }

  /// Construct by join of two points @a p and @a q (p. 53)
  constexpr pg_line(const pg_point<_K>& p, const pg_point<_K>& q) noexcept 
      : _Base{cross(p, q)} { }

  /// Return first element of line.
  constexpr _K a() const noexcept { return _Base::e1(); }

  /// Return second element of line.
  constexpr _K b() const noexcept { return _Base::e2(); }

  /// Return third element of line.
  constexpr _K c() const noexcept { return _Base::e3(); }

  /// Return true if a point @a p incident with line @a l
  bool incident(const pg_point<_K>& p) const noexcept
  { return dot(p, *this) == _K(0); }

  // Lets the compiler synthesize the assignment operator
  // pg_line<_K>& operator= (const pg_line<_K>&);    

};

// Operators:

/// Return true if @a p is equivalent to @a q (in projective sense).
template<typename _K>
inline constexpr bool
operator==(const pg_line<_K>& l, const pg_line<_K>& m) noexcept
{ return cross(l,m) == vector3d<_K>::zero; }

///  Return new point meet @a l and @a m (p. 53)
template<typename _K>
inline constexpr pg_point<_K>
meet(const pg_line<_K>& l, const pg_line<_K>& m) noexcept
{ return cross(l, m); }

/// Return incident of @a l and @a p
template <typename _K>
inline bool I(const pg_line<_K>& l, const pg_point<_K>& p)
{ return l.incident(p); }

///  Return new line join @a p and @a q (p. 53)
template<typename _K>
inline constexpr pg_line<_K>
aux1(const pg_line<_K>& p, const pg_line<_K>& q) noexcept
{ return pg_line<_K>{p + q}; }

///  Return new line join @a p and @a q (p. 53)
template<typename _K>
inline constexpr pg_point<_K>
aux2(const pg_line<_K>& p) noexcept { return pg_point<_K>{p}; }

///  Insertion operator for line values.
template<typename _K, class _Stream>
_Stream&
operator<<(_Stream& os, const pg_line<_K>& l)
{
  os << '<' << l.a() << ':' << l.b() << ':' << l.c() << '>';
  return os;
}

}

#endif
