// The template and inlines for the -*- C++ -*- cyclic line classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/cline.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_CLINE_HPP
#define FUN_CLINE_HPP 1

#include <sstream>
#include <cassert>
//#include <cpoint.hpp>

namespace fun 
{
  // Forward declarations.
  class cline;

  /** 
   *  Projective point represented by cyclic difference set
   *
   *  @param  Tp  Type of point elements
   */
  class cpoint
  {
  public:
    /// Default constructor.
    cpoint() : _m(0) { }
    
    cpoint(unsigned int m) : _m(m) { assert(_m < 13); }

    /// Return internal value    
    unsigned int value() const { return _m; }

    /// Construct by meet of two lines @a p and @a q
    cpoint(const cline& p, const cline& q);
    
    // Lets the compiler synthesize the assignment operator
    // cpoint& operator= (const cpoint&);    
    
  private:
    unsigned int _m;  
  };

  /**
   * @defgroup cyclic line
   * @ingroup geometry
   *
   * Classes and functions for cyclic line.
   * @{
   */

  /** 
   *  Projective line represented by cyclic difference set
   *
   *  @param  Tp  Type of line elements
   */
  class cline
  {
  public:
    /// Default constructor.
    cline() : _m(0) { }
    
    cline(unsigned int m) : _m(m) { assert(_m < 13); }

    /// Return internal value    
    unsigned int value() const { return _m; }

    /// Construct by join of two points @a p and @a q
    cline(const cpoint& p, const cpoint& q);
    
    // Lets the compiler synthesize the assignment operator
    // cline& operator= (const cline&);    
    
    /// Return true if a point @a p incident with this line
    bool
    incident(const cpoint& p) const
    { 
      static const unsigned int _quorum[4] = { 0, 1, 3, 9 };
      for (unsigned int i=0; i<4; ++i) 
	if ((value() + _quorum[i]) % 13 == p.value())
	  return true;
      return false;
    }

  private:
    unsigned int _m;  
  };


  // Operators:
  /// Return true if @a p is equal to @a q (in 3d affine sense).
  inline bool
  operator==(const cpoint& p, const cpoint& q)
  { return p.value() == q.value(); }

  /// Return true if @a p is equivalent to @a q (in projective sense).
  inline bool
  equiv(const cpoint& p, const cpoint& q)
  { return p == q; }

  /// Return false if @a p is equal to @a q.
  inline bool
  operator!=(const cpoint& p, const cpoint& q)
  { return !(p == q); }

  ///  Return new line join @a p and @a q (p. 53)
  inline cline
  join(const cpoint& p, const cpoint& q)
  { 
    assert(p != q);
    static const unsigned int _M[13] = 
      { 100, 0, 1, 0, 9, 9, 3, 9, 1, 0, 3, 3, 1 };
    unsigned int i = (q.value() + 13 - p.value()) % 13;
    return cline((p.value() + 13 - _M[i]) % 13); 
  }

  ///  Return determinant of @a l, @a m, @a n
  //xxx template<typename _K>
  //xxx inline _K
  //xxx det(const cpoint& l, const cpoint& m, const cpoint& n)
  //xxx { return det(l, m, n); }

  ///  Return true if @a p, @a q, @a r are collinear
  inline bool
  collinear(const cpoint& p, const cpoint& q, const cpoint& r)
  { return join(q,r).incident(p); }

  // ///  Return true if @a a V ( @a b, @a c, @a d, @a e) are harmonic (p. 102)
  // template<typename _K>
  // inline bool
  // harmonic(const cpoint& a, const cpoint& b, const cpoint& c,
  // 	   const cpoint& d, const cpoint& e)
  // { return det(a,b,d)*det(a,c,e) + det(a,b,e)*det(a,c,d) == 0; }

  // /// Return a line parallel to @a l and through @a p (p. 55)
  // template <typename _K>
  // inline cline parallel(const cline& p, const cline& l,
  // 			    const cline& l_Inf = cline(0))
  // { return join(p, meet(l, l_Inf)); }

  ///  Insertion operator for point values.
  template<typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& os, const cpoint& p)
  {
    std::basic_ostringstream<_CharT, _Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());
    s << '{' << p.value() << '}';
    return os << s.str();
  }


  // Operators:
  /// Return true if @a l is equal to @a m (in 3d affine sense).
  inline bool
  operator==(const cline& l, const cline& m)
  { return l.value() == m.value(); }

  /// Return true if @a l is equivalent to @a m (in projective sense).
  inline bool
  equiv(const cline& l, const cline& m)
  { return l == m; }

  /// Return false if @a l is equal to @a m.
  inline bool
  operator!=(const cline& l, const cline& m)
  { return !(l == m); }

  ///  Return new point meet @a l and @a m (p. 53)
  inline cpoint
  meet(const cline& l, const cline& m)
  { 
    assert(l != m);
    static unsigned int _M[13] = { 100, 1, 3, 3, 0, 1, 9, 3, 9, 9, 0, 1, 0 };
    unsigned int i = (m.value() + 13 - l.value()) % 13;
    return cpoint((_M[i] + l.value()) % 13); 
  }

  ///  Return determinant of @a l, @a m, @a n
  //xxx template<typename _K>
  //xxx inline _K
  //xxx det(const cline& l, const cline& m, const cline& n)
  //xxx { return det(l, m, n); }

  ///  Return true if @a l, @a m, @a n are concurrent
  inline bool
  concurrent(const cline& l, const cline& m, const cline& n)
  { return l.incident(meet(m,n)); }

  /// Return a line parallel to @a l and through @a p (p. 55)
  template <typename _K>
  inline cline parallel(const cpoint& p, const cline& l,
			    const cline& l_Inf = cline(0))
  { return join(p, meet(l, l_Inf)); }


  ///  Insertion operator for line values.
  template<typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& os, const cline& l)
  {
    static const unsigned int _quorum[4] = { 0, 1, 3, 9 };

    std::basic_ostringstream<_CharT, _Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());
    s << "{ ";
    for (unsigned int i=0; i<4; ++i) 
      s << (l.value() + _quorum[i])%13 << ' ';
    s << '}';
    return os << s.str();
  }

}

#endif
