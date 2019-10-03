// The template and inlines for the -*- C++ -*- 3d vector classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/vector3.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_VECTOR3_HPP
#define FUN_VECTOR3_HPP 1

namespace fun {
/**
 * @defgroup 3d_vector 3d Vector
 * @ingroup linear_alg
 *
 * Classes and functions for 3d vector.
 * @{
 */

// Forward declarations.
template <typename _K> struct vector3;

/**
 *  3-dimensional vector.
 *
 *  @param  Tp  Type of vector elements
 */
template <typename _K> struct vector3 {
  /// Value typedef.
  typedef _K value_type;

  /// Default constructor.
  ///  Unspecified parameters default to 0.
  constexpr vector3(const _K &e1, const _K &e2, const _K &e3) noexcept
      : _e1{e1}, _e2{e2}, _e3{e3} {}

  // Lets the compiler synthesize the copy constructor
  // vector3 (const vector3<_K>&);
  /// Copy constructor
  template <typename _Up>
  constexpr vector3(const vector3<_Up> &w) noexcept
      : _e1{w.e1()}, _e2{w.e2()}, _e3{w.e3()} {}

  /// Return first element of vector.
  constexpr _K e1() const noexcept { return _e1; }

  /// Return second element of vector.
  constexpr _K e2() const noexcept { return _e2; }

  /// Return third element of vector.
  constexpr _K e3() const noexcept { return _e3; }

  // Lets the compiler synthesize the assignment operator
  // vector3<_K>& operator= (const vector3<_K>&);
  /// Assign this vector to vector @a w.
  template <typename _Up> vector3<_K> &operator=(const vector3<_Up> &w) {
    _e1 = w.e1();
    _e2 = w.e2();
    _e3 = w.e3();
    return *this;
  }

  /// Add @a w to this vector.
  template <typename _Up> vector3<_K> &operator+=(const vector3<_Up> &w) {
    _e1 += w.e1();
    _e2 += w.e2();
    _e3 += w.e3();
    return *this;
  }

  /// Subtract @a w from this vector.
  template <typename _Up> vector3<_K> &operator-=(const vector3<_Up> &w) {
    _e1 -= w.e1();
    _e2 -= w.e2();
    _e3 -= w.e3();
    return *this;
  }

  /// Multiply this vector by @a a.
  vector3<_K> &operator*=(const _K &a) {
    _e1 *= a;
    _e2 *= a;
    _e3 *= a;
    return *this;
  }

  /// Divide this vector by @a a.
  vector3<_K> &operator/=(const _K &a) {
    _e1 /= a;
    _e2 /= a;
    _e3 /= a;
    return *this;
  }

private:
  _K _e1;
  _K _e2;
  _K _e3;
};

// Operators:
///  Return new vector @a v plus @a w.
template <typename _K>
inline vector3<_K> operator+(vector3<_K> v, const vector3<_K> &w) {
  return v += w;
}

///  Return new vector @a v plus @a w.
template <typename _K, typename _L>
inline constexpr auto operator+(const vector3<_K> &v,
                                const vector3<_L> &w) noexcept
    -> vector3<decltype(v.e1() + w.e1())> {
  return vector3<decltype(v.e1() + w.e1())>{v.e1() + w.e1(), v.e2() + w.e2(),
                                            v.e3() + w.e3()};
}

/// Return new vector @a v minus @a w.
template <typename _K>
inline vector3<_K> operator-(vector3<_K> v, const vector3<_K> &w) {
  return v -= w;
}

///  Return new vector @a v plus @a w.
template <typename _K, typename _L>
inline constexpr auto operator-(const vector3<_K> &v,
                                const vector3<_L> &w) noexcept
    -> vector3<decltype(v.e1() - w.e1())> {
  return vector3<decltype(v.e1() - w.e1())>{v.e1() - w.e1(), v.e2() - w.e2(),
                                            v.e3() - w.e3()};
}

//@{
///  Return new vector @a v times @a a.
template <typename _K>
inline vector3<_K> operator*(vector3<_K> v, const _K &a) {
  return v *= a;
}

template <typename _K>
inline vector3<_K> operator*(const _K &a, vector3<_K> v) {
  return v *= a;
}
//@}

template <typename _K, typename _Up>
inline constexpr auto operator*(const vector3<_K> &v, const _Up &a) noexcept
    -> vector3<decltype(v.e1() * a)> {
  return vector3<decltype(v.e1() * a)>{v.e1() * a, v.e2() * a, v.e3() * a};
}

template <typename _K, typename _Up>
inline constexpr auto operator*(const _Up &a, const vector3<_K> &v) noexcept
    -> vector3<decltype(a * v.e1())> {
  return vector3<decltype(a * v.e1())>{a * v.e1(), a * v.e2(), a * v.e3()};
}

///  Return new vector @a v divided by @a a.
template <typename _K>
inline vector3<_K> operator/(vector3<_K> v, const _K &a) {
  return v /= a;
}

template <typename _K, typename _Up>
inline constexpr auto operator/(const vector3<_K> &v, const _Up &a) noexcept
    -> vector3<decltype(v.e1() / a)> {
  return vector3<decltype(v.e1() / a)>{v.e1() / a, v.e2() / a, v.e3() / a};
}

/// Return @a v.
template <typename _K>
inline constexpr vector3<_K> operator+(const vector3<_K> &v) noexcept {
  return v;
}

/// Return negation of @a v/
template <typename _K>
inline constexpr vector3<_K> operator-(const vector3<_K> &v) noexcept {
  return vector3<_K>(-v.e1(), -v.e2(), -v.e3());
}

/// Return true if @a v is equal to @a w.
template <typename _K>
inline constexpr bool operator==(const vector3<_K> &v,
                                 const vector3<_K> &w) noexcept {
  return v.e1() == w.e1() && v.e2() == w.e2() && v.e3() == w.e3();
}

/// Return false if @a v is equal to @a w.
template <typename _K>
inline constexpr bool operator!=(const vector3<_K> &v,
                                 const vector3<_K> &w) noexcept {
  return !(v == w);
}

///  Return dot product of  @a v and @a w
template <typename _K>
inline constexpr _K dot(const vector3<_K> &v, const vector3<_K> &w) noexcept {
  return v.e1() * w.e1() + v.e2() * w.e2() + v.e3() * w.e3();
}

///  Return the quadrance of  @a v
template <typename _K>
inline constexpr _K quadrance(const vector3<_K> &v) noexcept {
  return dot(v, v);
}

///  Return new vector @a v x @a w (cross product).
template <typename _K>
inline constexpr vector3<_K> cross(const vector3<_K> &v,
                                   const vector3<_K> &w) noexcept {
  return vector3<_K>(v.e2() * w.e3() - v.e3() * w.e2(),
                     -v.e1() * w.e3() + v.e3() * w.e1(),
                     v.e1() * w.e2() - v.e2() * w.e1());
}

///  Return determinant of @a p,  @a q and @a r.
template <typename _K>
inline constexpr _K det(const vector3<_K> &p, const vector3<_K> &q,
                        const vector3<_K> &r) noexcept {
  return dot(p, cross(q, r)); // Pl\{"}ucker's formula
}

///  Insertion operator for vector values.
template <typename _K, class _Stream>
_Stream &operator<<(_Stream &os, const vector3<_K> &v) {
  os << '(' << v.e1() << ',' << v.e2() << ',' << v.e3() << ')';
  return os;
}
}

#endif
