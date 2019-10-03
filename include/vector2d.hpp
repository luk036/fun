// The template and inlines for the -*- C++ -*- 2d vector classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/vector2d.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_VECTOR2D_HPP
#define FUN_VECTOR2D_HPP 1

//#include <sstream>
//#include "rational.hpp"

namespace fun {
/**
 * @defgroup 2d_vector 2d Vector
 * @ingroup linear_alg
 *
 * Classes and functions for 2d vector.
 * @{
 */

// Forward declarations.
template <typename _K> struct vector2d;

/**
 *  2-dimensional vector.
 *
 *  @param  K  Type of vector elements
 */
template <typename _K> struct vector2d {
  /// Value typedef.
  typedef _K value_type;

  /// Default constructor.
  constexpr vector2d() noexcept : _e1{_K{0}}, _e2{_K{0}} {}

  /// Construct with two elements @a e1 and @a e2
  constexpr vector2d(const _K &e1, const _K &e2) noexcept : _e1{e1}, _e2{e2} {}

  // Lets the compiler synthesize the copy constructor
  // vector2d (const vector2d<_K>&);
  /// Copy constructor
  template <typename _Up>
  constexpr vector2d(const vector2d<_Up> &w) noexcept
      : _e1{w.e1()}, _e2{w.e2()} {}

  /// Return first element of vector.
  constexpr _K e1() const noexcept { return _e1; }

  /// Return second element of vector.
  constexpr _K e2() const noexcept { return _e2; }

  // Lets the compiler synthesize the assignment operator
  // vector2d<_K>& operator= (const vector2d<_K>&);
  /// Assign this vector to vector @a w.
  template <typename _Up> vector2d<_K> &operator=(const vector2d<_Up> &w) {
    _e1 = w.e1();
    _e2 = w.e2();
    return *this;
  }

  /// Add @a w to this vector.
  template <typename _Up> vector2d<_K> &operator+=(const vector2d<_Up> &w) {
    _e1 += w.e1();
    _e2 += w.e2();
    return *this;
  }

  /// Subtract @a w from this vector.
  template <typename _Up> vector2d<_K> &operator-=(const vector2d<_Up> &w) {
    _e1 -= w.e1();
    _e2 -= w.e2();
    return *this;
  }

  /// Multiply this vector by @a a.
  template <typename _Up> vector2d<_K> &operator*=(const _Up &a) {
    _e1 *= a;
    _e2 *= a;
    return *this;
  }

  /// Divide this vector by @a a.
  template <typename _Up> vector2d<_K> &operator/=(const _Up &a) {
    _e1 /= a;
    _e2 /= a;
    return *this;
  }

private:
  _K _e1;
  _K _e2;
};

// Operators:
///  Return new vector @a v plus @a w.
template <typename _K>
inline vector2d<_K> operator+(vector2d<_K> v, const vector2d<_K> &w) {
  return v += w;
}

///  Return new vector @a v plus @a w.
template <typename _K, typename _L>
inline constexpr auto operator+(const vector2d<_K> &v,
                                const vector2d<_L> &w) noexcept
    -> vector2d<decltype(v.e1() + w.e1())> {
  return vector2d<decltype(v.e1() + w.e1())>{v.e1() + w.e1(), v.e2() + w.e2()};
}

///  Return new vector @a v minus @a w.
template <typename _K>
inline vector2d<_K> operator-(vector2d<_K> v, const vector2d<_K> &w) {
  return v -= w;
}

///  Return new vector @a v minus @a w.
template <typename _K, typename _L>
inline constexpr auto operator-(const vector2d<_K> &v,
                                const vector2d<_L> &w) noexcept
    -> decltype(v + w) {
  return vector2d<decltype(v.e1() - w.e1())>{v.e1() - w.e1(), v.e2() - w.e2()};
}

//@{
///  Return new vector @a v times @a a.
template <typename _K>
inline vector2d<_K> operator*(vector2d<_K> v, const _K &a) {
  return v *= a;
}

template <typename _K, typename _Up>
inline constexpr auto operator*(const vector2d<_K> &v, const _Up &a) noexcept
    -> vector2d<decltype(v.e1() * a)> {
  return vector2d<decltype(v.e1() * a)>{v.e1() * a, v.e2() * a};
}

template <typename _K, typename _Up>
inline constexpr auto operator*(const _Up &a, const vector2d<_K> &v) noexcept
    -> vector2d<decltype(a * v.e1())> {
  return vector2d<decltype(a * v.e1())>{a * v.e1(), a * v.e2()};
}

// xxx template<typename _K, typename _R>
// xxx inline constexpr vector2d<_R>
// xxx operator*(const _R& a, const vector2d<_K>& v) noexcept
// xxx { return vector2d<_R>{a*v.e1(), a*v.e2()}; }
//@}

///  Return new vector @a v divided by @a a.
template <typename _K>
inline vector2d<_K> operator/(vector2d<_K> v, const _K &a) {
  return v /= a;
}

template <typename _K, typename _Up>
inline constexpr auto operator/(const vector2d<_K> &v, const _Up &a) noexcept
    -> vector2d<decltype(v.e1() / a)> {
  return vector2d<decltype(v.e1() / a)>{v.e1() / a, v.e2() / a};
}

/// Return @a v.
template <typename _K>
inline constexpr vector2d<_K> operator+(const vector2d<_K> &v) noexcept {
  return v;
}

/// Return negation of @a v/
template <typename _K>
inline constexpr vector2d<_K> operator-(const vector2d<_K> &v) noexcept {
  return vector2d<_K>(-v.e1(), -v.e2());
}

/// Return true if @a v is equal to @a w.
template <typename _K>
inline constexpr bool operator==(const vector2d<_K> &v,
                                 const vector2d<_K> &w) noexcept {
  return v.e1() == w.e1() && v.e2() == w.e2();
}

/// Return false if @a v is equal to @a w.
template <typename _K>
inline constexpr bool operator!=(const vector2d<_K> &v,
                                 const vector2d<_K> &w) noexcept {
  return !(v == w);
}

///  Return dot product of  @a v and @a w
template <typename _K>
inline constexpr _K dot(const vector2d<_K> &v, const vector2d<_K> &w) noexcept {
  return v.e1() * w.e1() + v.e2() * w.e2();
}

/// Return determinant of @a v and @a w/
template <typename _K>
inline constexpr _K det(const vector2d<_K> &v, const vector2d<_K> &w) noexcept {
  return v.e1() * w.e2() - v.e2() * w.e1();
}

/// Return cross ratio of @a a, @a b, @a c and @a d, i.e. (a,b;c,d)
template <typename _K>
inline constexpr _K cross_ratio(const vector2d<_K> &a, const vector2d<_K> &b,
                                const vector2d<_K> &c, const vector2d<_K> &d) {
  return det(a, c) * det(b, d) / (det(a, d) * det(b, c));
}

///  Insertion operator for vector values.
template <typename _K, class _Stream>
_Stream &operator<<(_Stream &os, const vector2d<_K> &v) {
  return os << '(' << v.e1() << ", " << v.e2() << ')';
}

///  Return the quadrance of  @a v
template <class Vector>
inline constexpr typename Vector::value_type
quadrance(const Vector &v) noexcept {
  return dot(v, v);
}

///  Return the spread of  @a v1 @a v2
template <class Vector>
inline typename Vector::value_type spread(const Vector &v1, const Vector &v2) {
  using _K = typename Vector::value_type;
  const _K dot12 = dot(v1, v2);
  return _K(1) - (dot12 / quadrance(v1)) * (dot12 / quadrance(v2));
}
}

#endif
