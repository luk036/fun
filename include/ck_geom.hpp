#ifndef _CK_GEOM_HPP
#define _CK_GEOM_HPP 1

#include "line3d.hpp"
#include "point3d.hpp"
#include "proj_geom.hpp"
#include "rational.hpp"

namespace fun {

template <typename T> constexpr T sq(const T &a) { return a * a; }

template <class P, class L>
concept bool Cayley_Klein_plane_h = Projective_plane_h<P, L> &&
requires(P A, P B, L l) {
  { ~A } -> L; // pole or polar
  {dot(A, l)}; // measure of A and l
};

/*
  axiom(P A, P B, L l) {
     ~~A == A;
     dot(A,l) == 0 => I(A,l);
  }
*/

template <class P, class L = typename P::dual>
concept bool Cayley_Klein_plane =
  Cayley_Klein_plane_h<P, L> && Cayley_Klein_plane_h<L, P>;

// general case
template <class P, class L>
auto quadrance(const P &p, const P &q)
    -> decltype(dot(P(), L()) / dot(P(), L())) {
  L lpq(p, q);
  return dot(lpq, ~lpq) / (dot(p, ~p) * dot(q, ~q));
}

template <class P, class L>
auto spread(const L &l, const L &m) 
    -> decltype(dot(P(), L()) / dot(P(), L())) {
  P Alm(l, m);
  return dot(Alm, ~Alm) / (dot(l, ~l) * dot(m, ~m));
}

/*
  namespace hyper {
    template<typename _K>
    constexpr line3d<_K>
    operator~(const point3d<_K>& p) noexcept
    { return vector3d<_K>(p.x(), p.y(), -p.z()); }

    template<typename _K>
    constexpr point3d<_K>
    operator~(const line3d<_K>& l) noexcept
    { return vector3d<_K>(l.x(), l.y(), -l.z()); }

    template<typename _K>
    constexpr _K
    dot(const point3d<_K>& p, const line3d<_K>& l) noexcept
    { return p * l; }

    template <class P, class L>
    auto quadrance(const P& p, const P& q)
      -> decltype(dot(p,~p)/dot(p,~p))
    {
        auto dpq = dot(p,~q);
        return (dpq/dot(p,~p))*(dpq/dot(q,~q)) - 1;
    }

    template <class P, class L>
    auto spread(const L& l, const L& m)
      -> decltype(dot(P,L)/dot(P,L))
    {
        auto dlm = dot(l,~m);
        return (dlm/dot(l,~l))*(dlm/dot(m,~m)) - 1;
    }
  }

  namespace ellip {
    template<typename _K>
    constexpr line3d<_K>
    operator~(const point3d<_K>& p) noexcept
    { return vector3d<_K>(p); }

    template<typename _K>
    constexpr point3d<_K>
    operator~(const line3d<_K>& l) noexcept
    { return vector3d<_K>(l); }

    template<typename _K>
    constexpr _K
    dot(const point3d<_K>& p, const line3d<_K>& l) noexcept
    { return p * l; }

    template <class P, class L>
    auto quadrance(const P& p, const P& q)
      -> decltype(dot(P,L)/dot(P,L))
    {
        auto dpq = dot(p,~q);
        return 1 - (dpq/dot(p,~p))*(dpq/dot(q,~q));
    }

    template <class P, class L>
    auto spread(const L& l, const L& m)
      -> decltype(dot(P,L)/dot(P,L))
    {
        auto dlm = dot(l,~m);
        return 1 - (dlm/dot(l,~l))*(dlm/dot(m,~m));
    }
  }

  // namespace euclid {
    ///  Return p^T*A*q

    template<typename _K>
    constexpr line3d<_K>
    operator~(const point3d<_K>& p) noexcept
    { return vector3d<_K>(0, 0, p.z()); }

    template<typename _K>
    constexpr point3d<_K>
    operator~(const line3d<_K>& l) noexcept
    { return vector3d<_K>(l.x(), l.y(), 0; }

    template<typename _K>
    constexpr _K
    dot(const point3d<_K>& p, const line3d<_K>& l) noexcept
    { return p * l; }

    template <class P, class L>
    template<typename _K>
    quadrance(const point3d<_K>& p, const point3d<_K>& q)
      -> decltype(p.x()/p.z())
    {
        return sq(p.x()/p.z() - q.x()/q.z()) +
               sq(p.y()/p.z() - q.y()/q.z())
    }

    template <class P, class L>
    auto spread(const L& l, const L& m)
      -> decltype(dot(P,L)/dot(P,L))
    {
        auto Alm = P(l,m);
        return dot(Alm,~Alm)/dot(l,~l)/dot(m,~m);
    }


    template<typename _K>
    inline constexpr _K
    omega(const point3d<_K>& p, const point3d<_K>& q) noexcept
    { return p.z()*q.z(); }

    ///  Return l^T*B*m
    template<typename _K>
    inline constexpr _K
    omega(const line3d<_K>& l, const line3d<_K>& m) noexcept
    { return l.a()*m.a() + l.b()*m.b(); }

    template <typename _K, class = typename
            std::enable_if<!std::is_integral<_K>::value>::type>
    inline auto
    quadrance(const point3d<_K>& p, const point3d<_K>& q)
      -> decltype(omega(p,p)/omega(q,q))
    {
      const line3d<_K> l = join(p,q);
      return omega(l,l)/omega(p,p)/omega(q,q);
    }

    template <typename _K, class = typename
            std::enable_if<std::is_integral<_K>::value>::type>
    inline rational<_K>
    quadrance(const point3d<_K>& p, const point3d<_K>& q)
    {
      const line3d<_K> l = join(p,q);
      return rational<_K>(omega(l,l),omega(p,p)) / omega(q,q);
    }
  // }
*/
}

#endif
