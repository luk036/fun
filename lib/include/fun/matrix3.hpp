// The template and inlines for the -*- C++ -*- 3x3 matrix classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/matrix3.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_MATRIX3_HPP
#define FUN_MATRIX3_HPP 1

#include "vector3.hpp"

namespace fun {
/**
 * @defgroup 3d_matrix 3x3 Matrix
 * @ingroup linear_alg
 *
 * Classes and functions for 3x3 matrix.
 * @{
 */

// Forward declarations.
template <typename _Tp> struct matrix3;

/**
 *  3x3 matrix. (a b c;
 *               d e f;
 *               g h i)
 *
 *  @param  Tp  Type of matrix elements
 */
template <typename _Tp> struct matrix3 {
  /// Value typedef.
  typedef _Tp value_type;

  /// Default constructor.
  constexpr matrix3() noexcept
      : _a{0}, _b{0}, _c{0}, _d{0}, _e{0}, _f{0}, _g{0}, _h{0}, _i{0} {}

  ///  Construct with its elements
  constexpr matrix3(const _Tp &a, const _Tp &b, const _Tp &c, const _Tp &d,
                    const _Tp &e, const _Tp &f, const _Tp &g, const _Tp &h,
                    const _Tp &i) noexcept
      : _a{a}, _b{b}, _c{c}, _d{d}, _e{e}, _f{f}, _g{g}, _h{h}, _i{i} {}

  // Lets the compiler synthesize the copy constructor
  // matrix3 (const matrix3<_Tp>&);
  /// Copy constructor
  template <typename _Up>
  constexpr matrix3(const matrix3<_Up> &B) noexcept
      : _a{B.a()}, _b{B.b()}, _c{B.c()}, _d{B.d()}, _e{B.e()}, _f{B.f()},
        _g{B.g()}, _h{B.h()}, _i{B.i()} {}

  /// Construct from vectors
  template <typename _Up>
  constexpr matrix3(const vector3<_Up> &v1, const vector3<_Up> &v2,
                    const vector3<_Up> &v3) noexcept
      : _a{v1.e1()}, _b{v2.e1()}, _c{v3.e1()}, _d{v1.e2()}, _e{v2.e2()},
        _f{v3.e2()}, _g{v1.e3()}, _h{v2.e3()}, _i{v3.e3()} {}

  /// Construct from outer_product of @a v1 and @a v2
  template <typename _Up>
  constexpr matrix3(const vector3<_Up> &v1, const vector3<_Up> &v2) noexcept
      : _a{v1.e1() * v2.e1()}, _b{v1.e1() * v2.e2()}, _c{v1.e1() * v2.e3()},
        _d{v1.e2() * v2.e1()}, _e{v1.e2() * v2.e2()}, _f{v1.e2() * v2.e3()},
        _g{v1.e3() * v2.e1()}, _h{v1.e3() * v2.e2()}, _i{v1.e3() * v2.e3()} {}

  /// Return first element of matrix.
  constexpr _Tp a() const noexcept { return _a; }

  /// Return second element of matrix.
  constexpr _Tp b() const noexcept { return _b; }

  /// Return third element of matrix.
  constexpr _Tp c() const noexcept { return _c; }

  /// Return fourth element of matrix.
  constexpr _Tp d() const noexcept { return _d; }

  /// Return fifth element of matrix.
  constexpr _Tp e() const noexcept { return _e; }

  /// Return sixth element of matrix.
  constexpr _Tp f() const noexcept { return _f; }

  /// Return seventh element of matrix.
  constexpr _Tp g() const noexcept { return _g; }

  /// Return eighth element of matrix.
  constexpr _Tp h() const noexcept { return _h; }

  /// Return ninth element of matrix.
  constexpr _Tp i() const noexcept { return _i; }

  // Lets the compiler synthesize the assignment operator
  // matrix3<_Tp>& operator= (const matrix3<_Tp>&);
  /// Assign this matrix to matrix @a B.
  template <typename _Up> matrix3<_Tp> &operator=(const matrix3<_Up> &B) {
    _a = B.a();
    _b = B.b();
    _c = B.c();
    _d = B.d();
    _e = B.e();
    _f = B.f();
    _g = B.g();
    _h = B.h();
    _i = B.i();
    return *this;
  }

  /// Add @a w to this matrix.
  template <typename _Up> matrix3<_Tp> &operator+=(const matrix3<_Up> &B) {
    _a += B.a();
    _b += B.b();
    _c += B.c();
    _d += B.d();
    _e += B.e();
    _f += B.f();
    _g += B.g();
    _h += B.h();
    _i += B.i();
    return *this;
  }

  /// Subtract @a w from this matrix.
  template <typename _Up> matrix3<_Tp> &operator-=(const matrix3<_Up> &B) {
    _a -= B.a();
    _b -= B.b();
    _c -= B.c();
    _d -= B.d();
    _e -= B.e();
    _f -= B.f();
    _g -= B.g();
    _h -= B.h();
    _i -= B.i();
    return *this;
  }

  /// Multiply this matrix by @a a.
  matrix3<_Tp> &operator*=(const _Tp &a) {
    _a *= a;
    _b *= a;
    _c *= a;
    _d *= a;
    _e *= a;
    _f *= a;
    _g *= a;
    _h *= a;
    _i *= a;
    return *this;
  }

  /// Divide this matrix by @a a.
  matrix3<_Tp> &operator/=(const _Tp &a) {
    _a /= a;
    _b /= a;
    _c /= a;
    _d /= a;
    _e /= a;
    _f /= a;
    _g /= a;
    _h /= a;
    _i /= a;
    return *this;
  }

  /// Return adjoint of this matrix (WildLinAlg8)
  constexpr matrix3<_Tp> adj() const noexcept {
    return matrix3<_Tp>(e() * i() - f() * h(), -(b() * i() - c() * h()),
                        b() * f() - c() * e(), -(d() * i() - f() * g()),
                        a() * i() - c() * g(), -(a() * f() - c() * d()),
                        d() * h() - e() * g(), -(a() * h() - b() * g()),
                        a() * e() - b() * d());
  }

  /// Return transpose of this matrix (WildLinAlg8)
  constexpr matrix3<_Tp> transpose() const noexcept {
    return matrix3<_Tp>(a(), d(), g(), b(), e(), h(), c(), f(), i());
  }

  /// Return determinant of this matrix (WildLinAlg8)
  constexpr _Tp det() const noexcept {
    return a() * (e() * i() - f() * h()) - b() * (d() * i() - f() * g()) +
           c() * (d() * h() - e() * g());
  }

private:
  _Tp _a, _b, _c;
  _Tp _d, _e, _f;
  _Tp _g, _h, _i;
};

// Operators:
///  Return new matrix @a A plus @a B.
template <typename _Tp>
inline matrix3<_Tp> operator+(matrix3<_Tp> A, const matrix3<_Tp> &B) {
  return A += B;
}

///  Return new matrix @a A minus @a B.
template <typename _Tp>
inline matrix3<_Tp> operator-(matrix3<_Tp> A, const matrix3<_Tp> &B) {
  return A -= B;
}

//@{
///  Return new matrix @a A times @a a.
template <typename _Tp>
inline matrix3<_Tp> operator*(matrix3<_Tp> A, const _Tp &a) {
  return A *= a;
}

template <typename _Tp>
inline matrix3<_Tp> operator*(const _Tp &a, matrix3<_Tp> A) {
  return A *= a;
}
//@}

///  Return new matrix @a A divided by @a a.
template <typename _Tp>
inline matrix3<_Tp> operator/(matrix3<_Tp> A, const _Tp &a) {
  return A /= a;
}

/// Return @a A.
template <typename _Tp>
inline constexpr matrix3<_Tp> operator+(const matrix3<_Tp> &A) noexcept {
  return A;
}

/// Return negation of @a A.
template <typename _Tp>
inline constexpr matrix3<_Tp> operator-(const matrix3<_Tp> &A) noexcept {
  return matrix3<_Tp>(-A.a(), -A.b(), -A.c(), -A.d(), -A.e(), -A.f(), -A.g(),
                      -A.h(), -A.i());
}

/// Return new matrix @a A times @a B.
template <typename _Tp>
inline constexpr matrix3<_Tp> operator*(const matrix3<_Tp> &A,
                                        const matrix3<_Tp> &B) noexcept {
  return matrix3<_Tp>(A.a() * B.a() + A.b() * B.d() + A.c() * B.g(),
                      A.a() * B.b() + A.b() * B.e() + A.c() * B.h(),
                      A.a() * B.c() + A.b() * B.f() + A.c() * B.i(),
                      A.d() * B.a() + A.e() * B.d() + A.f() * B.g(),
                      A.d() * B.b() + A.e() * B.e() + A.f() * B.h(),
                      A.d() * B.c() + A.e() * B.f() + A.f() * B.i(),
                      A.g() * B.a() + A.h() * B.d() + A.i() * B.g(),
                      A.g() * B.b() + A.h() * B.e() + A.i() * B.h(),
                      A.g() * B.c() + A.h() * B.f() + A.i() * B.i());
}

/// Return new matrix @a A times a vector @a v.
template <typename _Tp>
inline constexpr vector3<_Tp> operator*(const matrix3<_Tp> &A,
                                        const vector3<_Tp> &v) noexcept {
  return vector3<_Tp>(A.a() * v.e1() + A.b() * v.e2() + A.c() * v.e3(),
                      A.d() * v.e1() + A.e() * v.e2() + A.f() * v.e3(),
                      A.g() * v.e1() + A.h() * v.e2() + A.i() * v.e3());
}

/// Return true if @a A is equal to @a B.
template <typename _Tp>
inline constexpr bool operator==(const matrix3<_Tp> &A,
                                 const matrix3<_Tp> &B) noexcept {
  return A.a() == B.a() && A.b() == B.b() && A.c() == B.c() && A.d() == B.d() &&
         A.e() == B.e() && A.f() == B.f() && A.g() == B.g() && A.h() == B.h() &&
         A.i() == B.i();
}

/// Return false if @a A is equal to @a B.
template <typename _Tp>
inline constexpr bool operator!=(const matrix3<_Tp> &A,
                                 const matrix3<_Tp> &B) noexcept {
  return !(A == B);
}

/// Return transpose of this matrix (WildLinAlg8)
template <typename _Tp> matrix3<_Tp> transpose(const matrix3<_Tp> &A) noexcept {
  return matrix3<_Tp>(A.a(), A.d(), A.g(), A.b(), A.e(), A.h(), A.c(), A.f(),
                      A.i());
}

/// Return determinant of this matrix (WildLinAlg8)
template <typename _Tp> constexpr _Tp det(const matrix3<_Tp> &A) noexcept {
  return A.det();
}

///  Insertion operator for matrix values.
template <typename _Tp, class _Stream>
_Stream &operator<<(_Stream &os, const matrix3<_Tp> &A) {
  os << '(' << A.a() << ',' << A.b() << ',' << A.c() << ';' << A.d() << ','
     << A.e() << ',' << A.f() << ';' << A.g() << ',' << A.h() << ',' << A.i()
     << ')';
  return os;
}
}

#endif
