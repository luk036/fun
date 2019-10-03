// The template and inlines for the -*- C++ -*- 3d vector classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/valarray.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_VECTOR3D_HPP
#define FUN_VECTOR3D_HPP 1

#include <valarray>

namespace fun 
{
  
template <typename _K>
bool is_zero(const std::valarray<_K>& v)
{ return v[0] == _K(0) && v[1] == _K(0) && v[2] == _K(0); }

///  Return dot product of  @a v and @a w
template<typename _K>
inline constexpr _K
dot(const std::valarray<_K>& v, const std::valarray<_K>& w) noexcept
{ return (v*w).sum(); }

///  Return new vector @a v x @a w (cross product).
template<typename _K>
inline constexpr std::valarray<_K>
cross(const std::valarray<_K>& v, const std::valarray<_K>& w) noexcept
{
  return { 
     v[1]*w[2] - v[2]*w[1],
    -v[0]*w[2] + v[2]*w[0],
     v[0]*w[1] - v[1]*w[0]  };
}

///  Return determinant of @a p,  @a q and @a r.
template<typename _K>
inline constexpr _K
det(const std::valarray<_K>& p, const std::valarray<_K>& q, 
    const std::valarray<_K>& r) noexcept
{
  return dot(p, cross(q, r)); // Pl\{"}ucker's formula
}

///  Insertion operator for vector values.
template<typename _K, class _Stream>
_Stream& operator<<(_Stream& os, const std::valarray<_K>& v)
{
  os << '[' << v[0] << ',' << v[1] << ',' << v[2] << ']';
  return os;
}

///  Return the quadrance of  @a v 
template<typename _K>
inline constexpr _K
quadrance(const std::valarray<_K>& v) noexcept
{ return dot(v,v); }


} // namespace fun

#endif
