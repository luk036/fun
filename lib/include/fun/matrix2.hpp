// The template and inlines for the -*- C++ -*- 2x2 matrix classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/matrix2.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_MATRIX2_HPP
#define FUN_MATRIX2_HPP 1

#include <sstream>
#include "vector2.hpp"

namespace fun 
{
  /**
   * @defgroup 2d_matrix 2x2 Matrix
   * @ingroup linear_alg
   *
   * Classes and functions for 2x2 matrix.
   * @{
   */

  // Forward declarations.
  template<typename _Tp> struct matrix2;

  /** 
   *  2x2 matrix. (a c; 
   *               b d)
   *
   *  @param  Tp  Type of matrix elements
   */
  template <typename _Tp>
  struct matrix2
  {
    /// Value typedef.
    typedef _Tp value_type;
 
    /// Default constructor.
    constexpr matrix2() 
      : _a(0), _b(0), 
	_c(0), _d(0) { }

    ///  Unspecified parameters default to 0.
    constexpr matrix2(const _Tp& a, const _Tp& b,
		      const _Tp& c, const _Tp& d) 
      : _a(a), _b(b), 
	_c(c), _d(d) { }

    // Lets the compiler synthesize the copy constructor
    // matrix2 (const matrix2<_Tp>&);
    /// Copy constructor
    template<typename _Up>
    matrix2(const matrix2<_Up>& B) 
      : _a(B.a()), _b(B.b()), 
	_c(B.c()), _d(B.d()) { }

    /// Construct from vectors
    template<typename _Up>
    matrix2(const vector2<_Up>& v1, const vector2<_Up>& v2) 
      : _a(v1.e1()), _b(v2.e1()), 
	_c(v1.e2()), _d(v2.e2()) { }

    /// Return first element of matrix.
    constexpr _Tp a() { return _a; }

    /// Return second element of matrix.
    constexpr _Tp b() { return _b; }

    /// Return first element of matrix.
    constexpr _Tp c() { return _c; }

    /// Return second element of matrix.
    constexpr _Tp d() { return _d; }

    // Lets the compiler synthesize the assignment operator
    // matrix2<_Tp>& operator= (const matrix2<_Tp>&);
    /// Assign this matrix to matrix @a B.
    template<typename _Up>
    matrix2<_Tp>& operator=(const matrix2<_Up>& B)
    { 
      _a = B.a(); _b = B.b(); 
      _c = B.c(); _d = B.d(); 
      return *this; 
    }

    /// Add @a w to this matrix.
    template<typename _Up>
    matrix2<_Tp>& operator+=(const matrix2<_Up>& B)
    { 
      _a += B.a(); _b += B.b(); 
      _c += B.c(); _d += B.d();       
      return *this;
    }

    /// Subtract @a w from this matrix.
    template<typename _Up>
    matrix2<_Tp>& operator-=(const matrix2<_Up>& B)
    { 
      _a -= B.a(); _b -= B.b(); 
      _c -= B.c(); _d -= B.d();       
      return *this;
    }

    /// Multiply this matrix by @a a.
    matrix2<_Tp>& operator*=(const _Tp& a) 
    { 
      _a *= a; _b *= a; 
      _c *= a; _d *= a;       
      return *this;
    }

    /// Divide this matrix by @a a.
    matrix2<_Tp>& operator/=(const _Tp& a) 
    { 
      _a /= a; _b /= a; 
      _c /= a; _d /= a;       
      return *this;
    }

    /// Return determinant of this matrix
    _Tp det() { return _a * _d - _b * _c; }

  private:
    _Tp _a; _Tp _b;
    _Tp _c; _Tp _d;
  
  };

  // Operators:
  ///  Return new matrix @a A plus @a B.
  template<typename _Tp>
  inline matrix2<_Tp>
  operator+(const matrix2<_Tp>& A, const matrix2<_Tp>& B)
  {
    matrix2<_Tp> r = A;
    r += B;
    return r;
  }

  ///  Return new matrix @a A minus @a B.
  template<typename _Tp>
  inline matrix2<_Tp>
  operator-(const matrix2<_Tp>& A, const matrix2<_Tp>& B)
  {
    matrix2<_Tp> r = A;
    r -= B;
    return r;
  }

  //@{
  ///  Return new matrix @a A times @a a.
  template<typename _Tp>
  inline matrix2<_Tp>
  operator*(const matrix2<_Tp>& A, const _Tp& a)
  {
    matrix2<_Tp> r = A;
    r *= a;
    return r;
  }

  template<typename _Tp>
  inline matrix2<_Tp>
  operator*(const _Tp& a, const matrix2<_Tp>& A)
  {
    matrix2<_Tp> r = A;
    r *= a;
    return r;
  }
  //@}

  ///  Return new matrix @a A divided by @a a.
  template<typename _Tp>
  inline matrix2<_Tp>
  operator/(const matrix2<_Tp>& A, const _Tp& a)
  {
    matrix2<_Tp> r = A;
    r /= a;
    return r;
  }

  /// Return @a A.
  template<typename _Tp>
  inline matrix2<_Tp>
  operator+(const matrix2<_Tp>& A)
  { return A; }

  /// Return negation of @a A.
  template<typename _Tp>
  inline matrix2<_Tp>
  operator-(const matrix2<_Tp>& A)
  { return matrix2<_Tp>(-A.a(), -A.b(),
			-A.c(), -A.d()); }

  /// Return true if @a A is equal to @a B.
  template<typename _Tp>
  inline constexpr bool
  operator==(const matrix2<_Tp>& A, const matrix2<_Tp>& B)
  { return A.a() == B.a() && A.b() == B.b() 
      && A.c() == B.c() && A.d() == B.d(); }

  /// Return false if @a A is equal to @a B.
  template<typename _Tp>
  inline constexpr bool
  operator!=(const matrix2<_Tp>& A, const matrix2<_Tp>& B)
  { return !(A == B); }
  
  ///  Insertion operator for matrix values.
  template<typename _Tp, typename _CharT, class _Traits>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& os, const matrix2<_Tp>& A)
  {
    std::basic_ostringstream<_CharT, _Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());
    s << '(' << A.a() << ',' << A.b() 
      << ';' << A.c() << ',' << A.d() << ')';
    return os << s.str();
  }

}

#endif
