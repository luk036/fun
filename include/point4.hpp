// The template and inlines for the -*- C++ -*- 3d point classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/point3.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_POINT3_HPP
#define FUN_POINT3_HPP 1

#include <sstream>
#include "vector3.hpp"

namespace fun 
{
  /**
   * @defgroup 3d_point 3d Point in projective geometry
   * @ingroup geometry
   *
   * Classes and functions for 3d point.
   * @{
   */

  // Forward declarations.
  template<typename _K> class point3;
  template<typename _K> class line3;
  template<typename _K> struct point2;
  template<typename _K> class rational;

  /** 
   *  Projective point: one dimensional subspace of K^3
   *
   *  @param  K  Type of point elements
   */
  template <typename _K = int>
  class point3 : public vector3<_K>
    {
      /// Value typedef.
      typedef _K value_type;
      typedef vector3<_K> _Base;

    public:
      /// Default constructor.
      ///  Unspecified parameters default to 0.
      point3(const _K& x = _K(), 
	     const _K& y = _K(), 
	     const _K& z = _K(1)) 
        : _Base(x, y, z) { }

      /// Contruct from an affine point @a p.
      point3(const point2<_K>& p) : _Base(p.x(), p.y(), _K(1)) { }

      /// Construct from the base class
      point3(const vector3<_K>& v) : _Base(v) { }

      // Lets the compiler synthesize the copy constructor
      // point3 (const point3<_K>&);
      /// Copy constructor
      template<typename _Up>
      point3(const point3<_Up>& q) : _Base(q) { }

      /// Return the base class.
      constexpr vector3<_K> base() { return *this; }

      /// Construct by meet of two lines @a l and @a m. (p. 53)
      point3(const line3<_K>& l, const line3<_K>& m)
	: _Base(cross(l, m)) { }

      /// Return first element of point.
      constexpr _K x() { return _Base::e1(); }

      /// Return second element of point.
      constexpr _K y() { return _Base::e2(); }

      /// Return third element of point.
      constexpr _K z() { return _Base::e3(); }

      // Lets the compiler synthesize the assignment operator
      // point3<_K>& operator= (const point3<_K>&);    
      /// Assign this point to point @a q.
      template<typename _Up>
      point3<_K>& operator=(const point3<_Up>& q)
      { *this = q; return *this; }

      /// Add @a v to this point.
      //xxx template<typename _Up>
      //xxx point3<_K>& operator+=(const vector3<_Up>& v)
      //xxx { this->base() += v; return *this; }
      //xxx 
      //xxx /// Subtract @a v from this point.
      //xxx template<typename _Up>
      //xxx point3<_K>& operator-=(const vector3<_Up>& v)
      //xxx { this->base() -= v; return *this; }

      /// Return true if this point incident with a line @a l (p. 48)
      constexpr bool
      incident(const line3<_K>& l)
      { return dot(*this, l) == 0; }

    };

  // Operators:
  /// Return true if @a p is equal to @a q (in 3d affine sense).
  template<typename _K>
  inline bool
  operator==(const point3<_K>& p, const point3<_K>& q)
  { return p.x() == q.x() && p.y() == q.y() && p.z() == q.z(); }

  /// Return true if @a p is equivalent to @a q (in projective sense).
  template<typename _K>
  inline bool
  equiv(const point3<_K>& p, const point3<_K>& q)
  { return p.x()*q.z() == p.z()*q.x() && p.y()*q.z() == p.z()*q.y(); }

  /// Return false if @a p is equal to @a q.
  template<typename _K>
  inline bool
  operator!=(const point3<_K>& p, const point3<_K>& q)
  { return !(p == q); }

  ///  Return new point @a p plus @a v.
  //xxx template<typename _K>
  //xxx   inline point3<_K>
  //xxx   operator+(const point3<_K>& p, const vector3<_K>& v)
  //xxx   {
  //xxx     point3<_K> r = p;
  //xxx     r += v;
  //xxx     return r;
  //xxx   }
  //xxx 
  //xxx ///  Return new point @a p minus @a v.
  //xxx template<typename _K>
  //xxx   inline point3<_K>
  //xxx   operator-(const point3<_K>& p, const vector3<_K>& v)
  //xxx   {
  //xxx     point3<_K> r = p;
  //xxx     r -= v;
  //xxx     return r;
  //xxx   }
  //xxx 
  //xxx ///  Return new vector @a p minus @a q.
  //xxx template<typename _K>
  //xxx   inline vector3<_K>
  //xxx   operator-(const point3<_K>& p, const point3<_K>& q)
  //xxx   {
  //xxx     return p.base() - q.base();
  //xxx   }


  ///  Return new line join @a p and @a q (p. 53)
  template<typename _K>
  inline line3<_K>
  join(const point3<_K>& p, const point3<_K>& q)
  { return cross(p, q); }

  ///  Return determinant of @a a, @a b, @a c
  //xxx template<typename _K>
  //xxx inline _K
  //xxx det(const point3<_K>& a, const point3<_K>& b, const point3<_K>& c)
  //xxx { return det(a.base(), b.base(), c.base()); }

  ///  Return true if @a a, @a b, @a c are collinear (p. 102)
  template<typename _K>
  inline bool
  collinear(const point3<_K>& a, const point3<_K>& b, const point3<_K>& c)
  { return det(a,b,c) == _K(0); }

  ///  Return true if @a a V ( @a b, @a c, @a d, @a e) are harmonic (p. 102)
  template<typename _K>
  inline bool
  harmonic(const point3<_K>& a, const point3<_K>& b, const point3<_K>& c,
	   const point3<_K>& d, const point3<_K>& e)
  { 
    vector3<_K> ab = cross(a,b); vector3<_K> ac = cross(a,c);
    return dot(ab,d)*dot(ac,e) + dot(ab,e)*dot(ac,d) == _K(0); 
  }

  ///  Return true if @a a, @a b, @a c, @a d, @a e, @a f are on a conic  (p. 102)
  template<typename _K>
  inline bool
  on_a_conic(const point3<_K>& a, const point3<_K>& b, const point3<_K>& c,
	     const point3<_K>& d, const point3<_K>& e, const point3<_K>& f)
  { 
    vector3<_K> bc = cross(b,c); vector3<_K> ef = cross(e,f);
    vector3<_K> bf = cross(b,f); vector3<_K> ec = cross(e,c);
    return dot(a,bc)*dot(a,ef)*dot(d,bf)*dot(d,ec) 
      == dot(d,ef)*dot(d,bc)*dot(a,ec)*dot(a,bf); 
  }

  ///  Insertion operator for point values.
  template<typename _K, typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& os, const point3<_K>& p)
  {
    std::basic_ostringstream<_CharT, _Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());
    s << '[' << p.x() << ':' << p.y() << ':' << p.z() << ']';
    return os << s.str();
  }

}

#endif
