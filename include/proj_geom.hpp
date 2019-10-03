#ifndef _PROJ_GEOM_HPP
#define _PROJ_GEOM_HPP 1

#include "common_concepts.hpp"
#include <cassert>

/**
 @todo: projectivity >=
**/

namespace fun {

template <class P, class L>
concept bool Projective_plane_h = 
  Equality_comparable<P> && requires(P p, P q, L l) {
  { P(p) } -> P; // copyable
  { p.incident(l) } -> bool; // incidence
  { L(p, q) } -> L; // join or meet
};

/*
axiom(P p, P q, P r, L l) {
  l == {p, q} => I(p, l) && I(q, l);
}
*/

template <class P, class L = typename P::dual>
concept bool Projective_plane =
  Projective_plane_h<P, L> && Projective_plane_h<L, P>;

template <class P>
concept bool Projective_plane2 = Projective_plane<P>; // Make the compiler happy

///  Return true if @a p, @a q, @a r are collinear
Projective_plane2{P}
constexpr bool coincident(const P &p, const P &q, const P &r) {
  using L = typename P::dual;
  return r.incident(L{p, q});
}


///  Return true if @a p, @a q, @a r, @a s are collinear
Projective_plane2{P}
constexpr bool
coincident(const P& p, const P& q, const P& r, const P& s) {
  assert(p != q);
  const typename P::dual l{p, q};
  return incident(r, l) && incident(s, l);
}


template <class P, class L = typename P::dual>
requires Projective_plane<P, L> 
struct Project {
  const P &_o;
  project(const P &o) : _o{o} {}
  L operator()(const P &a) const { return L{a, _o}; }
};

template <class P, class L> 
requires Projective_plane<P, L> 
struct Perspect {
  const P &_p;
  const L &_l;
  Perspect(const P &p, const L &l) : _p{p}, _l{l} {}
  P operator()(const P &a) const { return P{{a, _p}, _l}; }
};

template <class P, class L = typename P::dual> 
requires Projective_plane<P, L> 
struct Perspectivity {
  const P &_p;
  Perspectivity(const P &p) : _p{p} {}
  bool operator()(const P &a1, const P &a2) const {
    return _p.incident(L{a1, a2});
  }
};

/*
/// Return a line parallel to @a l and through @a p (p. 55)
//luk Projective_plane { P, L }
inline constexpr L parallel(const P &p, const L &l, const L &l_Inf = L()) {
  return {p, {l, l_Inf}};
}
*/

template <class P, class L>
concept bool CompProjective_plane_h = 
  Projective_plane_h<P> && requires(P p, P q, L l) {
  { aux1(p, q) } -> P; // return a point on L(A,B)
  { aux2(p) } -> L; // return a line not pass A
};

/*
axiom(P p, P q, P r, L l) {
  r == aux1(p, q) => r != p && r != q;
  l == aux2(A) => !I(A, l);
}
*/

template <class P, class L = typename P::dual>
concept bool CompProjective_plane =
  CompProjective_plane_h<P> && CompProjective_plane_h<L>;

/// Return a harmonic point of @a a, @a b and @a c
CompProjective_plane { P, L }
inline P get_harmonic(const P &a, const P &b, const P &c) {
  // assert(incident(a, L{b, c}));
  const P o{aux2({a, b})}, g{aux2({a, c})};
  const L oa{o, a}, ob{o, b}, oc{o, c};
  const P p{oc, {a, g}}; // ???
  return {{a, b}, {{oa, {p, b}}, {ob, {p, a}}}};
}

} // namespace fun

#endif
