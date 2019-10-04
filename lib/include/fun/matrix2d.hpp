// The template and inlines for the -*- C++ -*- 2x2 matrix classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/matrix2d.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_MATRIX2D_HPP
#define FUN_MATRIX2D_HPP 1

#include "vector2d.hpp"

namespace fun {
/**
 * @defgroup 2d_matrix 2x2 Matrix
 * @ingroup linear_alg
 *
 * Classes and functions for 2x2 matrix.
 * @{
 */

// Forward declarations.
template <typename _Tp> struct matrix2d;

/**
 *  2x2 matrix. (a c;
 *               b d)
 *
 *  @param  Tp  Type of matrix elements
 */
template <typename _Tp> struct matrix2d {
  /// Value typedef.
  typedef _Tp value_type;

  /// Default constructor.
  constexpr matrix2d() noexcept : _a{0}, _b{0}, _c{0}, _d(0) {}

  ///  Unspecified parameters default to 0.
  constexpr matrix2d(const _Tp &a, const _Tp &b, const _Tp &c,
                     const _Tp &d) noexcept
      : _a{a}, _b{b}, _c{c}, _d{d} {}

  // Lets the compiler synthesize the copy constructor
  // matrix2d (const matrix2d<_Tp>&);
  /// Copy constructor
  template <typename _Up>
  constexpr matrix2d(const matrix2d<_Up> &B) noexcept
      : _a{B.a()}, _b{B.b()}, _c{B.c()}, _d{B.d()} {}

  /// Construct from vectors
  template <typename _Up>
  constexpr matrix2d(const vector2d<_Up> &v1, const vector2d<_Up> &v2) noexcept
      : _a{v1.e1()}, _b{v2.e1()}, _c{v1.e2()}, _d{v2.e2()} {}

  /// Return first element of matrix.
  constexpr _Tp a() const noexcept { return _a; }

  /// Return second element of matrix.
  constexpr _Tp b() const noexcept { return _b; }

  /// Return first element of matrix.
  constexpr _Tp c() const noexcept { return _c; }

  /// Return second element of matrix.
  constexpr _Tp d() const noexcept { return _d; }

  // Lets the compiler synthesize the assignment operator
  // matrix2d<_Tp>& operator= (const matrix2d<_Tp>&);
  /// Assign this matrix to matrix @a B.
  template <typename _Up> matrix2d<_Tp> &operator=(const matrix2d<_Up> &B) {
    _a = B.a();
    _b = B.b();
    _c = B.c();
    _d = B.d();
    return *this;
  }

  /// Add @a w to this matrix.
  template <typename _Up> matrix2d<_Tp> &operator+=(const matrix2d<_Up> &B) {
    _a += B.a();
    _b += B.b();
    _c += B.c();
    _d += B.d();
    return *this;
  }

  /// Subtract @a w from this matrix.
  template <typename _Up> matrix2d<_Tp> &operator-=(const matrix2d<_Up> &B) {
    _a -= B.a();
    _b -= B.b();
    _c -= B.c();
    _d -= B.d();
    return *this;
  }

  /// Multiply this matrix by @a a.
  matrix2d<_Tp> &operator*=(const _Tp &a) {
    _a *= a;
    _b *= a;
    _c *= a;
    _d *= a;
    return *this;
  }

  /// Divide this matrix by @a a.
  matrix2d<_Tp> &operator/=(const _Tp &a) {
    _a /= a;
    _b /= a;
    _c /= a;
    _d /= a;
    return *this;
  }

  /// Return adjoint of this matrix
  constexpr matrix2d<_Tp> adj() const noexcept {
    return matrix2d<_Tp>(d(), -b(), -c(), a());
  }

  /// Return transpose of this matrix
  constexpr matrix2d<_Tp> transpose() const noexcept {
    return matrix2d<_Tp>(a(), c(), b(), d());
  }

  /// Return determinant of this matrix
  constexpr _Tp det() const noexcept { return _a * _d - _b * _c; }

private:
  _Tp _a;
  _Tp _b;
  _Tp _c;
  _Tp _d;
};

// Operators:
///  Return new matrix @a A plus @a B.
template <typename _Tp>
inline constexpr matrix2d<_Tp> operator+(matrix2d<_Tp> A,
                                         const matrix2d<_Tp> &B) noexcept {
  return A += B;
}

///  Return new matrix @a A minus @a B.
template <typename _Tp>
inline constexpr matrix2d<_Tp> operator-(matrix2d<_Tp> A,
                                         const matrix2d<_Tp> &B) noexcept {
  return A -= B;
}

//@{
///  Return new matrix @a A times @a a.
template <typename _Tp>
inline constexpr matrix2d<_Tp> operator*(matrix2d<_Tp> A,
                                         const _Tp &a) noexcept {
  return A *= a;
}

template <typename _Tp>
inline matrix2d<_Tp> operator*(const _Tp &a, matrix2d<_Tp> A) {
  return A *= a;
}
//@}

///  Return new matrix @a A divided by @a a.
template <typename _Tp>
inline matrix2d<_Tp> operator/(matrix2d<_Tp> A, const _Tp &a) {
  A /= a;
  return A;
}

/// Return @a A.
template <typename _Tp>
inline constexpr matrix2d<_Tp> operator+(const matrix2d<_Tp> &A) noexcept {
  return A;
}

/// Return negation of @a A.
template <typename _Tp>
inline constexpr matrix2d<_Tp> operator-(const matrix2d<_Tp> &A) noexcept {
  return matrix2d<_Tp>(-A.a(), -A.b(), -A.c(), -A.d());
}

/// Return true if @a A is equal to @a B.
template <typename _Tp>
inline constexpr bool operator==(const matrix2d<_Tp> &A,
                                 const matrix2d<_Tp> &B) noexcept {
  return A.a() == B.a() && A.b() == B.b() && A.c() == B.c() && A.d() == B.d();
}

/// Return false if @a A is equal to @a B.
template <typename _Tp>
inline constexpr bool operator!=(const matrix2d<_Tp> &A,
                                 const matrix2d<_Tp> &B) noexcept {
  return !(A == B);
}

///  Insertion operator for matrix values.
template <typename _Tp, class _Stream>
_Stream &operator<<(_Stream &os, const matrix2d<_Tp> &A) {
  os << '(' << A.a() << ',' << A.b() << ';' << A.c() << ',' << A.d() << ')';
  return os;
}
}

#endif
