#include <conic3.hpp>
#include <point3.hpp>
#include <line3.hpp>
#include <vector3.hpp>

using namespace fun;

/// Construct by five points
template<typename _K>
conic3<_K>::conic3(const point3<_K>& p1, const point3<_K>& p2, 
		   const point3<_K>& p3, const point3<_K>& p4, 
		   const point3<_K>& p5)
{
  line3<_K> g1 { p1, p3 };
  line3<_K> g2 { p2, p4 };
  line3<_K> h1 { p1, p4 };
  line3<_K> h2 { p2, p3 };
  matrix3<_K> G { g1, g2 };
  matrix3<_K> H { h1, h2 };
  vector3<_K> q = p5;
  matrix3<_K> M = (dot(q,h1)*dot(h2,q)) * G - (dot(q,g1)*dot(g2,q)) * H;
  A() = M + M.transpose();
}
