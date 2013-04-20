// The template and inlines for the -*- C++ -*- 2d point classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/point2.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_POINT2_HPP
#define FUN_POINT2_HPP 1

#include <sstream>
#include "vector2.hpp"

namespace fun 
{
  /**
   * @defgroup 2d_point 2d Point
   * @ingroup geometry
   *
   * Classes and functions for 2d point.
   * @{
   */

  // Forward declarations.
  template<typename _K> struct point2;
  template<typename _K> class line3;

  /** 
   *  2-dimensional point. 
   *
   *  @param  Tp  Type of point elements
   */
  template <typename _K>
    struct point2
    {
      /// Value typedef.
      typedef _K value_type;
 
      /// Default constructor.
      ///  Unspecified parameters default to 0.
      constexpr point2(const _K& x = _K(), const _K& y = _K()) 
        : _x(x), _y(y) { }
      // Lets the compiler synthesize the copy constructor
      // point2 (const point2<_K>&);
      /// Copy constructor
      template<typename _Up>
      point2(const point2<_Up>& q) : _x(q.x()), _y(q.y()) { }

      /// Return first element of point.
      constexpr _K x() { return _x; }

      /// Return second element of point.
      constexpr _K y() { return _y; }

      // Lets the compiler synthesize the assignment operator
      // point2<_K>& operator= (const point2<_K>&);
      /// Assign this point to point @a q.
      template<typename _Up>
      point2<_K>& operator=(const point2<_Up>& q)
      { _x = q.x(); _y = q.y(); return *this; }

      /// Add @a v to this point.
      template<typename _Up>
      point2<_K>& operator+=(const vector2<_Up>& v)
      { _x += v.e1(); _y += v.e2(); return *this; }

      /// Subtract @a v from this point.
      template<typename _Up>
      point2<_K>& operator-=(const vector2<_Up>& v)
      { _x -= v.e1(); _y -= v.e2(); return *this; }


    private:
      _K _x;
      _K _y;
    
    };

  // Operators:
  ///  Return new point @a p plus @a v.
  template<typename _K>
    inline point2<_K>
    operator+(const point2<_K>& p, const vector2<_K>& v)
    {
      point2<_K> r = p;
      r += v;
      return r;
    }

  ///  Return new point @a p minus @a v.
  template<typename _K>
    inline point2<_K>
    operator-(const point2<_K>& p, const vector2<_K>& v)
    {
      point2<_K> r = p;
      r -= v;
      return r;
    }

  ///  Return new vector @a p minus @a q.
  template<typename _K>
    inline vector2<_K>
    operator-(const point2<_K>& p, const point2<_K>& q)
    {
      return vector2<_K>(p.x() - q.x(), p.y() - q.y());
    }

  /// Return negation of @a p
  template<typename _K>
    inline point2<_K>
    operator-(const point2<_K>& p)
    { return point2<_K>(-p.x(), -p.y()); }

  /// Return true if @a p is equal to @a q.
  template<typename _K>
    inline constexpr bool
    operator==(const point2<_K>& p, const point2<_K>& q)
    { return p.x() == q.x() && p.y() == q.y(); }

  /// Return false if @a p is equal to @a q.
  template<typename _K>
    inline constexpr bool
    operator!=(const point2<_K>& p, const point2<_K>& q)
    { return p.x() != q.x() || p.y() != q.y(); }

  ///  Return new line join @a p and @a q (p. 53)
  template<typename _K>
  inline line3<_K>
  join(const point2<_K>& p, const point2<_K>& q)
  { return line3<_K>(p.y()-q.y(), -p.x()+q.x(), p.x()*q.y() - p.y()*q.x()); }

  ///  Return true if @a a, @a b, @a c are collinear
  template<typename _K>
  inline bool
  collinear(const point2<_K>& a, const point2<_K>& b, const point2<_K>& c)
  { return det(a-c, b-c) == 0; }

  ///  Return true if @a a, @a b, @a c, @a d, @a e, @a f are on a conic
  template<typename _K>
  inline bool
  on_a_conic(const point2<_K>& a, const point2<_K>& b, const point2<_K>& c,
	     const point2<_K>& d, const point2<_K>& e, const point2<_K>& f)
  { 
    vector2<_K> ca = a - c;  vector2<_K> fa = a - f;
    vector2<_K> cb = b - c;  vector2<_K> fb = b - f;
    vector2<_K> cd = d - c;  vector2<_K> fd = d - f;
    vector2<_K> ce = e - c;  vector2<_K> fe = e - f;

    return det(ca,cb)*det(fa,fe)*det(fd,fb)*det(cd,ce) 
      - det(fd,fe)*det(cd,cb)*det(ca,ce)*det(fa,fb) == 0; 
  }


  ///  Insertion operator for point values.
  template<typename _K, typename _CharT, class _Traits>
    std::basic_ostream<_CharT, _Traits>&
    operator<<(std::basic_ostream<_CharT, _Traits>& os, const point2<_K>& p)
    {
      std::basic_ostringstream<_CharT, _Traits> s;
      s.flags(os.flags());
      s.imbue(os.getloc());
      s.precision(os.precision());
      s << '[' << p.x() << ',' << p.y() << ']';
      return os << s.str();
    }

}

#endif
