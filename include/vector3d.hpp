// The template and inlines for the -*- C++ -*- 3d vector classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/vector3d.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_VECTOR3D_HPP
#define FUN_VECTOR3D_HPP 1

#include <boost/operators.hpp>   // for boost::addable etc

namespace fun 
{
  
/** 
 *  3-dimensional vector. 
 *
 *  @param  Tp  Type of vector elements
 */
template <typename _K>
class vector3d :
  boost::equality_comparable < vector3d<_K>,
  boost::addable < vector3d<_K>,
  boost::subtractable < vector3d<_K>,
  boost::multipliable2 < vector3d<_K>, _K,
  boost::dividable2 < vector3d<_K>, _K
  > > > > >
{
  /// Value typedef.
  typedef _K value_type;

public:
  /// static memeber zero
  static const vector3d<_K> zero;

  /// Default constructor. 
  constexpr vector3d<_K>(
    const _K& e1, 
    const _K& e2, 
    const _K& e3) noexcept
    : _e1{e1}, _e2{e2}, _e3{e3} { }

  /// Return first element of vector.
  constexpr _K e1() const noexcept { return _e1; }
  /// Return second element of vector.
  constexpr _K e2() const noexcept { return _e2; }
  /// Return third element of vector.
  constexpr _K e3() const noexcept { return _e3; }

  // Lets the compiler synthesize the assignment operator
  // vector3d<_K>& operator= (const vector3d<_K>&);
  /// Assign this vector to vector @a w.
  /// Add @a w to this vector.
  vector3d<_K>& operator+=(const vector3d<_K>& w)
  { _e1 += w.e1(); _e2 += w.e2(); _e3 += w.e3(); return *this; }

  /// Subtract @a w from this vector.
  vector3d<_K>& operator-=(const vector3d<_K>& w)
  { _e1 -= w.e1(); _e2 -= w.e2(); _e3 -= w.e3(); return *this; }

  /// Multiply this vector by @a a.
  vector3d<_K>& operator*=(const _K& a) 
  { _e1 *= a; _e2 *= a; _e3 *= a; return *this; }

  /// Divide this vector by @a a.
  vector3d<_K>& operator/=(const _K& a) 
  { _e1 /= a; _e2 /= a; _e3 /= a; return *this; }
  
  constexpr bool operator== (const vector3d<_K>& w) const
  { return e1() == w.e1() && e2() == w.e2() && e3() == w.e3(); }

private:
  _K _e1;
  _K _e2;
  _K _e3;  
};

template <typename _K>
const vector3d<_K> vector3d<_K>::zero (_K(0), _K(0), _K(0)); 

/// Return @a v.
template<typename _K>
inline constexpr vector3d<_K>
operator+(const vector3d<_K>& v) noexcept
{ return v; }

/// Return negation of @a v/
template<typename _K>
inline constexpr vector3d<_K>
operator-(const vector3d<_K>& v) noexcept
{ return vector3d<_K>(-v.e1(), -v.e2(), -v.e3()); }

///  Return dot product of  @a v and @a w
template<typename _K>
inline constexpr _K
dot(const vector3d<_K>& v, const vector3d<_K>& w) noexcept
{ return v.e1()*w.e1() + v.e2()*w.e2() + v.e3()* w.e3(); }

///  Return new vector @a v x @a w (cross product).
template<typename _K>
inline constexpr vector3d<_K>
cross(const vector3d<_K>& v, const vector3d<_K>& w) noexcept
{
  return vector3d<_K>( 
     v.e2()*w.e3() - v.e3()*w.e2(),
    -v.e1()*w.e3() + v.e3()*w.e1(),
     v.e1()*w.e2() - v.e2()*w.e1()  );
}

///  Return determinant of @a p,  @a q and @a r.
template<typename _K>
inline constexpr _K
det(const vector3d<_K>& p, const vector3d<_K>& q, 
    const vector3d<_K>& r) noexcept
{
  return dot(p, cross(q, r)); // Pl\{"}ucker's formula
}

///  Insertion operator for vector values.
template<typename _K, class _Stream>
_Stream& operator<<(_Stream& os, const vector3d<_K>& v)
{
  os << '[' << v.e1() << ',' << v.e2() << ',' << v.e3() << ']';
  return os;
}

///  Return the quadrance of  @a v 
template<typename _K>
inline constexpr _K
quadrance(const vector3d<_K>& v) noexcept
{ return dot(v,v); }


} // namespace fun

#endif
