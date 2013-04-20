// The template and inlines for the -*- C++ -*- 2d vector classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/vector2.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_VECTOR2_HPP
#define FUN_VECTOR2_HPP 1

#include <sstream>
//#include "rational.hpp"

namespace fun 
{
  /**
   * @defgroup 2d_vector 2d Vector
   * @ingroup linear_alg
   *
   * Classes and functions for 2d vector.
   * @{
   */

  // Forward declarations.
  template<typename _K> struct vector2;

  /** 
   *  2-dimensional vector. 
   *
   *  @param  K  Type of vector elements
   */
  template <typename _K>
  struct vector2
  {
    /// Value typedef.
    typedef _K value_type;
 
    /// Default constructor.
    constexpr vector2() : _e1(_K(0)), _e2(_K(0)) { }

    /// Construct with two elements @a e1 and @a e2 
    constexpr vector2(const _K& e1, const _K& e2) 
      : _e1(e1), _e2(e2) { }

    // Lets the compiler synthesize the copy constructor
    // vector2 (const vector2<_K>&);
    /// Copy constructor
    template<typename _Up>
    vector2(const vector2<_Up>& w) 
      : _e1(w.e1()), _e2(w.e2()) { }

    /// Return first element of vector.
    constexpr _K e1() { return _e1; }

    /// Return second element of vector.
    constexpr _K e2() { return _e2; }

    // Lets the compiler synthesize the assignment operator
    // vector2<_K>& operator= (const vector2<_K>&);
    /// Assign this vector to vector @a w.
    template<typename _Up>
    vector2<_K>& operator=(const vector2<_Up>& w)
    { _e1 = w.e1(); _e2 = w.e2(); return *this; }

    /// Add @a w to this vector.
    template<typename _Up>
    vector2<_K>& operator+=(const vector2<_Up>& w)
    { _e1 += w.e1(); _e2 += w.e2(); return *this; }

    /// Subtract @a w from this vector.
    template<typename _Up>
    vector2<_K>& operator-=(const vector2<_Up>& w)
    { _e1 -= w.e1(); _e2 -= w.e2(); return *this; }

    /// Multiply this vector by @a a.
    vector2<_K>& operator*=(const _K& a) 
    { _e1 *= a; _e2 *= a; return *this; }

    /// Divide this vector by @a a.
    vector2<_K>& operator/=(const _K& a) 
    { _e1 /= a; _e2 /= a; return *this; }
  

  private:
    _K _e1;
    _K _e2;
  
  };

  // Operators:
  ///  Return new vector @a v plus @a w.
  template<typename _K>
  inline vector2<_K>
  operator+(const vector2<_K>& v, const vector2<_K>& w)
  {
    vector2<_K> r = v;
    r += w;
    return r;
  }

  ///  Return new vector @a v minus @a w.
  template<typename _K>
  inline vector2<_K>
  operator-(const vector2<_K>& v, const vector2<_K>& w)
  {
    vector2<_K> r = v;
    r -= w;
    return r;
  }

  //@{
  ///  Return new vector @a v times @a a.
  template<typename _K>
  inline vector2<_K>
  operator*(const vector2<_K>& v, const _K& a)
  {
    vector2<_K> r = v;
    r *= a;
    return r;
  }

  template<typename _K>
  inline vector2<_K>
  operator*(const _K& a, const vector2<_K>& v)
  {
    vector2<_K> r = v;
    r *= a;
    return r;
  }
  //@}

  ///  Return new vector @a v divided by @a a.
  template<typename _K>
  inline vector2<_K>
  operator/(const vector2<_K>& v, const _K& a)
  {
    vector2<_K> r = v;
    r /= a;
    return r;
  }

  /// Return @a v.
  template<typename _K>
  inline vector2<_K>
  operator+(const vector2<_K>& v)
  { return v; }

  /// Return negation of @a v/
  template<typename _K>
  inline vector2<_K>
  operator-(const vector2<_K>& v)
  { return vector2<_K>(-v.e1(), -v.e2()); }

  /// Return true if @a v is equal to @a w.
  template<typename _K>
  inline constexpr bool
  operator==(const vector2<_K>& v, const vector2<_K>& w)
  { return v.e1() == w.e1() && v.e2() == w.e2(); }

  /// Return false if @a v is equal to @a w.
  template<typename _K>
  inline constexpr bool
  operator!=(const vector2<_K>& v, const vector2<_K>& w)
  { return !(v == w); }

  ///  Return dot product of  @a v and @a w
  template<typename _K>
  inline _K
  dot(const vector2<_K>& v, const vector2<_K>& w)
  { return v.e1()*w.e1() + v.e2()*w.e2(); }

  /// Return determinant of @a v and @a w/
  template<typename _K>
  inline _K
  det(const vector2<_K>& v, const vector2<_K>& w)
  { return v.e1()*w.e2() - v.e2()*w.e1(); }

  /// Return the cross ratio of @a a, @a b, @a c and @a d
  // template<typename _K>
  // inline rational<_K>
  // cross_ratio(const vector2<_K>& a, const vector2<_K>& b,
  // 	      const vector2<_K>& c, const vector2<_K>& d)
  // {
  //   return rational<_K>(det(a,c)*det(b,d), det(a,d)*det(b,c));
  //}

  ///  Insertion operator for vector values.
  template<typename _K, typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& os, const vector2<_K>& v)
  {
    std::basic_ostringstream<_CharT, _Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());
    s << '(' << v.e1() << ',' << v.e2() << ')';
    return os << s.str();
  }

}

#endif
