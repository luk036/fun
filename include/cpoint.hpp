// The template and inlines for the -*- C++ -*- cyclic point classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/cpoint.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_CPOINT_HPP
#define FUN_CPOINT_HPP 1

#include <sstream>
#include <cassert>
#include <cline.hpp>

namespace fun 
{
  /**
   * @defgroup cyclic point
   * @ingroup geometry
   *
   * Classes and functions for cyclic point.
   * @{
   */

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
    unsigned int value() { return _m; }

    /// Construct by meet of two lines @a p and @a q
    cpoint(const cline& p, const cline& q);
    
    // Lets the compiler synthesize the assignment operator
    // cpoint& operator= (const cpoint&);    
    
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

}

#endif
