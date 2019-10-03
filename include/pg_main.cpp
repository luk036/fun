/*
http : // melpon.org/wandbox/permlink/dXn3Nf0rK30qcN6x
*/

#include "common_concepts.hpp"
#include "pg_line.hpp"
#include "pg_point.hpp"
#include "proj_geom.hpp"
#include <initializer_list>
#include <iostream>
#include <list>

using namespace fun;

int main() {
  using P = pg_point<int>;
  using L = pg_line<int>;
  const P p(1, 2, 3), q(3, 2, 3), r(-1, 3, 4);
  const L l(1, -2, 3), m(-3, 2, 1), n(3, 4, -5);
  std::cout << p << '\n'
            << l << '\n'
            << incident(q, l) << '\n'
            << coincident(p, q, p) << '\n'
            << coincident(l, m, n) << '\n'
            << '\n';
}