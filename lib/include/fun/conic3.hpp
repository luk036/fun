// The template and inlines for the -*- C++ -*- conic3 classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/conic3.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_CONIC3_HPP
#define FUN_CONIC3_HPP 1

#include "matrix3.hpp"

namespace fun {
/**
 * @defgroup 3d_conic3 3d Conic3 in projective geometry
 * @ingroup geometry
 *
 * Classes and functions for 3d conic3.
 * @{
 */

// Forward declarations.
template <typename _K> class point3;
template <typename _K> class line3;
template <typename _K> struct point2;
// template<typename _K> class rational;

/**
 *  Projective conic3 represented by homogenous coordinates.
 *
 *  @param  Tp  Type of conic3 elements
 */
template <typename _K = int> class conic3 : private matrix3<_K> {
  /// Value typedef.
  typedef _K value_type;
  typedef matrix3<_K> _Base;

public:
  /// Default constructor.
  constexpr conic3(const _K &a, const _K &b, const _K &c, const _K &d,
                   const _K &e, const _K &f) noexcept
      : _Base{a, b, d, b, c, e, d, e, f} {}

  /// Construct from a matrix @a A
  explicit constexpr conic3(const matrix3<_K> &M) noexcept
      : _Base{M + M.transpose()} {}

  // Lets the compiler synthesize the copy constructor
  // conic3 (const conic3<_K>&);
  /// Copy constructor
  template <typename _Up>
  constexpr conic3(const conic3<_Up> &C) noexcept : _Base{C.base()} {}

  /// Return the base class
  constexpr matrix3<_K> A() const noexcept { return *this; }

  /// Construct by five points
  conic3(const point3<_K> &a, const point3<_K> &b, const point3<_K> &c,
         const point3<_K> &d, const point3<_K> &e);

  /// Return first element of conic3.
  constexpr _K a() const noexcept { return _Base::a(); }

  /// Return second element of conic3.
  constexpr _K b() const noexcept { return _Base::d(); }

  /// Return third element of conic3.
  constexpr _K c() const noexcept { return _Base::e(); }

  /// Return first element of conic3.
  constexpr _K d() const noexcept { return _Base::g(); }

  /// Return second element of conic3.
  constexpr _K e() const noexcept { return _Base::h(); }

  /// Return third element of conic3.
  constexpr _K f() const noexcept { return _Base::i(); }

  // Lets the compiler synthesize the assignment operator
  // conic3<_K>& operator= (const conic3<_K>&);

  constexpr line3<_K> polar(const point3<_K> &p) const noexcept {
    return A() * p;
  }

  /// Return true if a point @a p incident with this conic3
  constexpr bool incident(const point3<_K> &p) const noexcept {
    return polar(p).incident(p);
  }
};

// Operators:
/// Return true if @a C1 is equal to @a C2 (in 3d affine sense).
template <typename _K>
inline bool constexpr operator==(const conic3<_K> &C1,
                                 const conic3<_K> &C2) noexcept {
  return C1.A() == C2.A();
}

/// Return false if @a C2 is equal to @a C2.
template <typename _K>
inline bool constexpr operator!=(const conic3<_K> &C1,
                                 const conic3<_K> &C2) noexcept {
  return !(C1 == C2);
}

///  Insertion operator for conic3 values.
template <typename _K, class _Stream>
_Stream &operator<<(_Stream &os, const conic3<_K> &l) {
  os << '<' << l.a() << ':' << l.b() << ':' << l.c() << l.d() << ':' << l.e()
     << ':' << l.f() << '>';
  return os;
}
}

#endif
