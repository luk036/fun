#include "matrix2.hpp"
#include "point3.hpp"
#include "point2.hpp"
#include "vector2.hpp"
#include "rational.hpp"
#include "vector3.hpp"
#include "line3.hpp"
#include "proj_geom.hpp"
#include "matrix3.hpp"
#include <iostream>

int main()
{
  using namespace fun;

  point3<> A{1,1}, B{3,2},C{3,0}, D{4,1};
  line3<> lAB{A, B}, lCD{C, D};
  point3<> E{lAB, lCD};
  std::cout << E << '\n';

  matrix3<int> A3 {1, -2, 3, 0, 4, 1, 2, -3, 7 };
  std::cout << A3.det() << '\n';
  std::cout << A3.adj() << '\n';
  std::cout << A3 * A3.adj() << '\n';

  vector3<int> vv {3, 4, 5}; // C++11
  vector3<int> ww = 2*vv;
  std::cout << cross(vv,ww) << '\n';
  std::cout << A3 * vv << '\n';

  line3<int> l1 {4,5,6};
  std::cout << l1 << '\n';

  rational<> r1 {4}, r2 {5,8}; // C++11
  std::cout << r1 + r2 << '\n';

  point3<> p3 {3, 4, 6};
  std::cout << p3 << '\n';
  point3<> p4 {3, 5, 2};
  line3<int> l4 {p3, p4};

  std::cout << l4 << '\n';
  std::cout << meet(l1, l4) << '\n';
  std::cout << parallel(p4, l4) << '\n';

  vector2<int> v; // zero vector
  vector2<int> w {3, 4};
  vector2<vector2<int>> R {v, w};
  std::cout << R << '\n';

  matrix2<int> A2 {1, 2, 3, 4 };
  std::cout << A2 << '\n';

  point2<rational<> > p(r1, r2);
  p += w;
  std::cout << p << std::endl;  
}
