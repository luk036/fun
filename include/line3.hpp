// The template and inlines for the -*- C++ -*- 3d line classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/line3.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_LINE3_HPP
#define FUN_LINE3_HPP 1

#include <sstream>
#include "vector3.hpp"

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
  template<typename _K> class point3;
  template<typename _K> class line3;
  template<typename _K> struct point2;
  template<typename _K> class rational;

  /** 
   *  Projective line represented by homogenous coordinates. 
   *
   *  @param  Tp  Type of line elements
   */
  template <typename _K = int>
  class line3 : public vector3<_K>
    {
      /// Value typedef.
      typedef _K value_type;
      typedef vector3<_K> _Base;

    public:
      /// Default constructor.
      ///  Unspecified parameters default to 0 (line at Infinity).
      line3(const _K& x = _K(), 
	    const _K& y = _K(), 
	    const _K& z = _K(1)) 
        : _Base(x, y, z) { }

      /// Construct from the base class @a v
      line3(const vector3<_K>& v) : _Base(v) { }

      // Lets the compiler synthesize the copy constructor
      // line3 (const line3<_K>&);
      /// Copy constructor
      template<typename _Up>
      line3(const line3<_Up>& q) : _Base(q) { }

      /// Return the base class
      constexpr vector3<_K> base() { return *this; }

      /// Construct by join of two points @a p and @a q (p. 53)
      line3(const point3<_K>& p, const point3<_K>& q) 
	: _Base(cross(p, q)) { }

      /// Return first element of line.
      constexpr _K a() { return _Base::e1(); }

      /// Return second element of line.
      constexpr _K b() { return _Base::e2(); }

      /// Return third element of line.
      constexpr _K c() { return _Base::e3(); }

      // Lets the compiler synthesize the assignment operator
      // line3<_K>& operator= (const line3<_K>&);    

      /// Return true if a point @a p incident with this line
      constexpr bool
      incident(const point3<_K>& p)
      { return dot(p, *this) == _K(0); }

    };

  // Operators:
  /// Return true if @a p is equal to @a q (in 3d affine sense).
  template<typename _K>
  inline bool
  operator==(const line3<_K>& l, const line3<_K>& m)
  { return l.a() == m.a() && l.b() == m.b() && l.c() == m.c(); }

  /// Return true if @a p is equivalent to @a q (in projective sense).
  template<typename _K>
  inline bool
  equiv(const line3<_K>& l, const line3<_K>& m)
  { return l.a()*m.c() == l.c()*m.a() && l.b()*m.c() == l.c()*m.b(); }

  /// Return false if @a p is equal to @a q.
  template<typename _K>
  inline bool
  operator!=(const line3<_K>& l, const line3<_K>& m)
  { return !(l == m); }


  ///  Return new point meet @a l and @a m (p. 53)
  template<typename _K>
  inline point3<_K>
  meet(const line3<_K>& l, const line3<_K>& m)
  { return cross(l, m); }

  ///  Return determinant of @a l, @a m, @a n
  //xxx template<typename _K>
  //xxx inline _K
  //xxx det(const line3<_K>& l, const line3<_K>& m, const line3<_K>& n)
  //xxx { return det(l.base(), m.base(), n.base()); }

  ///  Return true if @a l, @a m, @a n are concurrent
  template<typename _K>
  inline bool
  concurrent(const line3<_K>& l, const line3<_K>& m, const line3<_K>& n)
  { return det(l,m,n) == _K(0); }

  // ///  Return true if @a a V ( @a b, @a c, @a d, @a e) are harmonic (p. 102)
  // template<typename _K>
  // inline bool
  // harmonic(const line3<_K>& a, const line3<_K>& b, const line3<_K>& c,
  // 	   const line3<_K>& d, const line3<_K>& e)
  // { return det(a,b,d)*det(a,c,e) + det(a,b,e)*det(a,c,d) == 0; }

  /// Return a line parallel to @a l and through @a p (p. 55)
  template <typename _K>
  inline line3<_K> parallel(const point3<_K>& p, const line3<_K>& l,
			    const line3<_K>& l_Inf = line3<_K>(0,0,1))
  { return join(p, meet(l, l_Inf)); }


  ///  Insertion operator for line values.
  template<typename _K, typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& os, const line3<_K>& l)
  {
    std::basic_ostringstream<_CharT, _Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());
    s << '<' << l.a() << ':' << l.b() << ':' << l.c() << '>';
    return os << s.str();
  }

}

#endif
