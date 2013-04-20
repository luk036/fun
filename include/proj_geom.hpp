#ifndef _PROJ_GEOM_HPP
#define _PROJ_GEOM_HPP 1

//xxx #include "point3.hpp"
//xxx #include "line3.hpp"
//xxx #include "point2.hpp"

namespace fun {

  //xxx /// Return projected point
  //xxx template <typename _K>
  //xxx constexpr point2<_K> project(const point3<_K>& p)
  //xxx { return point2<_K>(p.x()/p.z(), p.y()/p.z()); }
  //xxx 
  //xxx /// Return true if a point @a p incident with a line @a l (p. 48)
  //xxx template <typename _K>
  //xxx constexpr bool
  //xxx incident(const point3<_K>& p, const line3<_K>& l)
  //xxx { return dot(p.base(), l.base()) == 0; }

  ///  Return true if @a l, @a m, @a n are concurrent
  template <class Line>
  inline bool
  concurrent(const Line& l, const Line& m, const Line& n)
  { return l.incident(meet(m,n)); }

  ///  Return true if @a p, @a q, @a r are collinear
  template <class Point>
  inline bool
  collinear(const Point& p, const Point& q, const Point& r)
  { return join(q,r).incident(p); }

  /// Return a line parallel to @a l and through @a p (p. 55)
  template <class Point, class Line>
  inline Line parallel(const Point& p, const Line& l,
		       const Line& l_Inf = Line())
  { return join(p, meet(l, l_Inf)); }
  
}

#endif
