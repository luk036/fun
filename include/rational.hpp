// The template and inlines for the -*- C++ -*- rational number classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/rational.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_RATIONAL_HPP
#define FUN_RATIONAL_HPP 1

#include <sstream>
#include <cassert>

namespace fun 
{
  /**
   * @defgroup rational (extended) Rational Number
   * @ingroup arithmetic
   *
   * Classes and functions for (extended) rational number.
   * Reference: MF103-
   * @{
   */

  // Forward declarations.
  template<typename _Z> struct rational;

  /** 
   *  Rational number. 
   *
   *  @param  Z  Type of rational number elements
   */
  template <typename _Z = int>
    struct rational
    {
      /// Value typedef.
      typedef _Z value_type;
 
      /// Default constructor.
      ///  Unspecified parameters default to 0.
      rational(const _Z& p = _Z(), const _Z& q = _Z(1)) : _p(p), _q(q) { }

      // Lets the compiler synthesize the copy constructor
      // rational (const rational<_Z>&);
      /// Copy constructor
      template<typename _Up>
      rational(const rational<_Up>& s) : _p(s.nom()), _q(s.denom()) { }

      /// Return first element of rational number.
      constexpr _Z nom() { return _p; }

      /// Return second element of rational number.
      constexpr _Z denom() { return _q; }

      /// Normalize rational number.
      void normalize() { if (_q < _Z()) { _p = -_p; _q = -_q; } }

      // Lets the compiler synthesize the assignment operator
      // rational<_Z>& operator= (const rational<_Z>&);
      /// Assign this rational number to rational number @a s.
      template<typename _Up>
      rational<_Z>& operator=(const rational<_Up>& s)
      { _p = s.nom(); _q = s.denom(); return *this; }

      /// Add @a s to this rational number.
      template<typename _Up>
      rational<_Z>& operator+=(const rational<_Up>& s)
      { 
        _p = _p * s.denom() + _q * s.nom(); 
        _q = _q * s.denom();
        normalize(); 
        return *this;
      }

      /// Subtract @a s from this rational number.
      template<typename _Up>
      rational<_Z>& operator-=(const rational<_Up>& s)
      { 
        _p = _p * s.denom() - _q * s.nom(); 
        _q = _q * s.denom();
        return *this;
      }

      /// Multiply @a s to this rational number.
      template<typename _Up>
      rational<_Z>& operator*=(const rational<_Up>& s)
      { 
        _p *= s.nom(); 
        _q *= s.denom();
        return *this;
      }

      /// Divide @a s to this rational number.
      template<typename _Up>
      rational<_Z>& operator/=(const rational<_Up>& s)
      { 
        _p *= s.denom(); 
        _q *= s.nom();
        return *this;
      }

      /// Add @a s to this rational number.
      rational<_Z>& operator+=(const _Z& a)
      { _p += _q * a; return *this; }

      /// Subtract @a s from this rational number.
      rational<_Z>& operator-=(const _Z& a)
      { _p -= _q * a; return *this; }

      /// Multiply this rational number by @a a.
      rational<_Z>& operator*=(const _Z& a) 
      { _p *= a; return *this; }

      /// Divide this rational number by @a a.
      rational<_Z>& operator/=(const _Z& a) 
      { _q *= a; return *this; }
    

    private:
      _Z _p;
      _Z _q;
    
    };

  // Operators:
  ///  Return new rational number @a r plus @a s.
  template<typename _Z>
    inline rational<_Z>
    operator+(const rational<_Z>& r, const rational<_Z>& s)
    {
      rational<_Z> res = r;
      res += s;
      return res;
    }

  ///  Return new rational number @a r minus @a s.
  template<typename _Z>
    inline rational<_Z>
    operator-(const rational<_Z>& r, const rational<_Z>& s)
    {
      rational<_Z> res = r;
      res -= s;
      return res;
    }

  //@{
  ///  Return new rational number @a r times @a a.
  template<typename _Z>
    inline rational<_Z>
  operator*(const rational<_Z>& r, const rational<_Z>& s)
    {
      rational<_Z> res = r;
      res *= s;
      return res;
    }

  template<typename _Z>
    inline rational<_Z>
    operator*(const rational<_Z>& r, const _Z& a)
    {
      rational<_Z> res = r;
      res *= a;
      return res;
    }

  template<typename _Z>
    inline rational<_Z>
    operator*(const _Z& a, const rational<_Z>& r)
    {
      rational<_Z> res = r;
      res *= a;
      return res;
    }
  //@}

  ///  Return new rational number @a r divided by @a a.
  template<typename _Z>
    inline rational<_Z>
    operator/(const rational<_Z>& r, const _Z& a)
    {
      rational<_Z> res = r;
      res /= a;
      return res;
    }

  /// Return @a r.
  template<typename _Z>
    inline rational<_Z>
    operator+(const rational<_Z>& r)
    { return r; }

  /// Return negation of @a r
  template<typename _Z>
    inline rational<_Z>
    operator-(const rational<_Z>& r)
    { return rational<_Z>(-r.nom(), r.denom()); }

  /// Return true if @a r is equal to @a s.
  template<typename _Z>
    inline bool
    operator==(const rational<_Z>& r, const rational<_Z>& s)
    { 
      assert(!(r.nom() == 0 && r.denom() == 0)); // NaN
      assert(!(s.nom() == 0 && s.denom() == 0)); // NaN
      return r.nom() * s.denom() == r.denom() * s.nom(); // -Inf == +Inf ???
    }

  /// Return false if @a r is equal to @a s.
  template<typename _Z>
    inline bool
    operator!=(const rational<_Z>& r, const rational<_Z>& s)
    { return !(r == s); }

  /// Return true if @a r is less than @a s.
  template<typename _Z>
    inline bool
    operator<(const rational<_Z>& r, const rational<_Z>& s)
    { 
      assert(!(r.nom() == 0 && r.denom() == 0)); // NaN
      assert(!(s.nom() == 0 && s.denom() == 0)); // NaN
      _Z a = r.nom();
      _Z b = r.denom();
      _Z c = s.nom();
      _Z d = s.denom();
      if (b < 0) { a = -a; b = -b; }
      if (d < 0) { c = -c; d = -d; }
      return a*d < b*c; // problem with -\Inf, +Inf
    }

  ///  Insertion operator for rational number values.
  template<typename _Z, typename _CharT, class _Traits>
    std::basic_ostream<_CharT, _Traits>&
    operator<<(std::basic_ostream<_CharT, _Traits>& os, const rational<_Z>& r)
    {
      std::basic_ostringstream<_CharT, _Traits> s;
      s.flags(os.flags());
      s.imbue(os.getloc());
      s.precision(os.precision());
      const _Z a = r.nom();
      const _Z b = r.denom();
      if (a == 0) {
        if (b == 0) {
          s << "NaN";
        } else {
          s << '0';
        }
      } else {
        if (b == 0) {
          if (a > 0) {
            s << "Inf";
          } else {
            s << "-Inf";
          } 
	} else if (b == 1) {
          s << a;
        } else {
          s << '(' << a << '/' << b << ')';
        }
      }
      return os << s.str();
    }

}

#endif
