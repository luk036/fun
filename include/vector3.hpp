// The template and inlines for the -*- C++ -*- 3d vector classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/vector3.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_VECTOR3_HPP
#define FUN_VECTOR3_HPP 1

#include <sstream>
//#include "rational.hpp"
//#include "matrix3.hpp"

namespace fun 
{
  /**
   * @defgroup 3d_vector 3d Vector
   * @ingroup linear_alg
   *
   * Classes and functions for 3d vector.
   * @{
   */

  // Forward declarations.
  template<typename _K> struct vector3;

  /** 
   *  3-dimensional vector. 
   *
   *  @param  Tp  Type of vector elements
   */
  template <typename _K>
  struct vector3
  {
    /// Value typedef.
    typedef _K value_type;
 
    /// Default constructor.
    ///  Unspecified parameters default to 0.
    constexpr vector3(const _K& e1, const _K& e2, const _K& e3) 
      : _e1(e1), _e2(e2), _e3(e3) { }

    // Lets the compiler synthesize the copy constructor
    // vector3 (const vector3<_K>&);
    /// Copy constructor
    template<typename _Up>
    vector3(const vector3<_Up>& w) 
      : _e1(w.e1()), _e2(w.e2()), _e3(w.e3()) { }

    /// Return first element of vector.
    constexpr _K e1() { return _e1; }

    /// Return second element of vector.
    constexpr _K e2() { return _e2; }

    /// Return third element of vector.
    constexpr _K e3() { return _e3; }

    // Lets the compiler synthesize the assignment operator
    // vector3<_K>& operator= (const vector3<_K>&);
    /// Assign this vector to vector @a w.
    template<typename _Up>
    vector3<_K>& operator=(const vector3<_Up>& w)
    { _e1 = w.e1(); _e2 = w.e2(); _e3 = w.e3(); return *this; }

    /// Add @a w to this vector.
    template<typename _Up>
    vector3<_K>& operator+=(const vector3<_Up>& w)
    { _e1 += w.e1(); _e2 += w.e2(); _e3 += w.e3(); return *this; }

    /// Subtract @a w from this vector.
    template<typename _Up>
    vector3<_K>& operator-=(const vector3<_Up>& w)
    { _e1 -= w.e1(); _e2 -= w.e2(); _e3 -= w.e3(); return *this; }

    /// Multiply this vector by @a a.
    vector3<_K>& operator*=(const _K& a) 
    { _e1 *= a; _e2 *= a; _e3 *= a; return *this; }

    /// Divide this vector by @a a.
    vector3<_K>& operator/=(const _K& a) 
    { _e1 /= a; _e2 /= a; _e3 /= a; return *this; }
  

  private:
    _K _e1;
    _K _e2;
    _K _e3;
  
  };

  // Operators:
  ///  Return new vector @a v plus @a w.
  template<typename _K>
  inline vector3<_K>
  operator+(const vector3<_K>& v, const vector3<_K>& w)
  {
    vector3<_K> r = v;
    r += w;
    return r;
  }

  ///  Return new vector @a v minus @a w.
  template<typename _K>
  inline vector3<_K>
  operator-(const vector3<_K>& v, const vector3<_K>& w)
  {
    vector3<_K> r = v;
    r -= w;
    return r;
  }

  //@{
  ///  Return new vector @a v times @a a.
  template<typename _K>
  inline vector3<_K>
  operator*(const vector3<_K>& v, const _K& a)
  {
    vector3<_K> r = v;
    r *= a;
    return r;
  }

  template<typename _K>
  inline vector3<_K>
  operator*(const _K& a, const vector3<_K>& v)
  {
    vector3<_K> r = v;
    r *= a;
    return r;
  }
  //@}

  ///  Return new vector @a v divided by @a a.
  template<typename _K>
  inline vector3<_K>
  operator/(const vector3<_K>& v, const _K& a)
  {
    vector3<_K> r = v;
    r /= a;
    return r;
  }

  /// Return @a v.
  template<typename _K>
  inline vector3<_K>
  operator+(const vector3<_K>& v)
  { return v; }

  /// Return negation of @a v/
  template<typename _K>
  inline vector3<_K>
  operator-(const vector3<_K>& v)
  { return vector3<_K>(-v.e1(), -v.e2(), -v.e3()); }

  /// Return true if @a v is equal to @a w.
  template<typename _K>
  inline constexpr bool
  operator==(const vector3<_K>& v, const vector3<_K>& w)
  { return v.e1() == w.e1() && v.e2() == w.e2() && v.e3() == w.e3(); }

  /// Return false if @a v is equal to @a w.
  template<typename _K>
  inline constexpr bool
  operator!=(const vector3<_K>& v, const vector3<_K>& w)
  { return !(v == w); }

  ///  Return dot product of  @a v and @a w
  template<typename _K>
  inline _K
  dot(const vector3<_K>& v, const vector3<_K>& w)
  { return v.e1()*w.e1() + v.e2()*w.e2() + v.e3()* w.e3(); }

  ///  Return new vector @a v x @a w (cross product).
  template<typename _K>
  inline vector3<_K>
  cross(const vector3<_K>& v, const vector3<_K>& w)
  {
    return vector3<_K>( v.e2()*w.e3() - v.e3()*w.e2(),
		       -v.e1()*w.e3() + v.e3()*w.e1(),
			v.e1()*w.e2() - v.e2()*w.e1());
  }

  ///  Return determinant of @a p,  @a q and @a r.
  template<typename _K>
  inline _K
  det(const vector3<_K>& p, const vector3<_K>& q, const vector3<_K>& r)
  {
    return dot(p, cross(q, r)); // Pl\{"}ucker's formula
  }


  ///  Insertion operator for vector values.
  template<typename _K, typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& os, const vector3<_K>& v)
  {
    std::basic_ostringstream<_CharT, _Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());
    s << '(' << v.e1() << ',' << v.e2() << ',' << v.e3() << ')';
    return os << s.str();
  }

}

#endif
