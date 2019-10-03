#include "pg_line.hpp"
#include "pg_point.hpp"
#include "proj_geom.hpp"
#include <cassert>
#include <iostream>


using namespace fun;

int main() {
  pg_point<int> p1{3, 2, 1};
  pg_point<int> p2{-3, 2, 1};
  pg_point<int> p3{3, 2, -1};
  pg_line<int> l1{13, 2, 1};
  pg_line<int> l2{3, 12, 1};
  pg_line<int> l3{3, 2, 11};
  assert(I({p1, p2}, p1));
  assert(collinear(p1, p2, aux1(p1, p2)));
  std::cout << p1 << '\n';
}