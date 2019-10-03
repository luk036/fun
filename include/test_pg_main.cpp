#include "pg_line.hpp"
#include "pg_point.hpp"
#include "proj_geom.hpp"
#include <cassert>
#include <iostream>

using namespace fun;

int main() {
  pg_point<int> p = {3, 2, 1};
  pg_point<int> q = {-3, 1, 2};
  pg_point<int> r = {1, -2, 3};
  pg_line<int> l = {-2, 3, -2};

  pg_line<int> m = {p, q};
  assert(I(m, p) && I(m, q));
  assert(I(p, l) == I(l, p));
  assert(collinear(p, q, aux1(p, q)));
  assert(!I(p, aux2(p)));

  pg_line<int> nan = {p, p};

  std::cout << I(p, l) << '\n';
  std::cout << collinear(p, q, r) << '\n';
  std::cout << pg_line<int>{p, q} << '\n';
}