// The template and inlines for the -*- C++ -*- rational number classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/rational.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_RATIONAL_HPP
#define FUN_RATIONAL_HPP 1

#include <cassert>
#include <type_traits> // is_integral<T>
#include <boost/operators.hpp>

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
  //template<typename _Z> struct rational;

  /// greatest common divider
  template<typename _Z, class = typename
	    std::enable_if<std::is_integral<_Z>::value>::type> 
  //xxx requires is_integral<_Z>::value
  inline constexpr _Z gcd(const _Z& a, const _Z& b) noexcept
  { return b == _Z(0) ? abs(a) : gcd(b, a%b); }
  
  /** 
   *  Rational number. 
   *
   *  @param  Z  Type of rational number elements
   *  @todo unit testing
   */
  template <typename _Z, class = typename
	    std::enable_if<std::is_integral<_Z>::value>::type>
  //xxx requires is_integral<_Z>::value
  struct rational : boost::ordered_field_operators<rational<_Z>,
		    boost::ordered_field_operators2<rational<_Z>, _Z> >
  {
    /// Value typedef.
    typedef _Z value_type;
    
    /// Default constructor.
    ///  Unspecified parameters default to 0.
    explicit 
    rational(const _Z& p = _Z(), const _Z& q = _Z(1)) 
      : _num{p}, _denom{q} 
    {
      assert(!(_num == _Z(0) && _denom == _Z(0)));
      normalize(); 
    }

    // Lets the compiler synthesize the copy constructor
    //rational (const rational<_Z>&) = default;

    /// Copy constructor
    template<typename _Up>
    explicit constexpr 
    rational(const rational<_Up>& s) noexcept 
      : _num{s.num()}, _denom{s.denom()} 
    { }
    
    /// Return first element of rational number.
    constexpr _Z num() const noexcept { return _num; }
    
    /// Return second element of rational number.
    constexpr _Z denom() const noexcept { return _denom; }
    
    // Lets the compiler synthesize the assignment operator
    // rational<_Z>& operator= (const rational<_Z>&);
    /// Assign this rational number to rational number @a s.
    template<typename _Up>
    rational<_Z>& operator=(const rational<_Up>& s)
    { _num = s.num(); _denom = s.denom(); return *this; }

    /// Increase this rational number (prefix operator)
    rational<_Z>& operator++()
    { _num += _denom; return *this; }

    /// Decrease this rational number (prefix operator)
    rational<_Z>& operator--()
    { _num -= _denom; return *this; }

    /// Increase this rational number (postfix operator)
    rational<_Z> operator++(int)
    { rational<_Z> res(*this); ++(*this); return res; }

    /// Decrease this rational number (postfix operator)
    rational<_Z> operator--(int)
    { rational<_Z> res(*this); --(*this); return res; }
        
    /// Add @a s to this rational number.
    rational<_Z>& operator+=(const _Z& a)
    { _num += _denom * a; return *this; }

    /// Subtract @a s from this rational number.
    rational<_Z>& operator-=(const _Z& a)
    { _num -= _denom * a; return *this; }
    
    /// Multiply this rational number by @a a.
    rational<_Z>& operator*=(const _Z& a) 
    { _num *= a; normalize(); return *this; }
    
    /// Divide this rational number by @a a.
    rational<_Z>& operator/=(const _Z& a) 
    { _denom *= a; normalize(); return *this; }

    /// Add @a s to this rational number.
    template<typename _Up>
    rational<_Z>& operator+=(const rational<_Up>& s)
    { 
      _num = _num * s.denom() + _denom * s.num(); 
      _denom *= s.denom();
      normalize(); 
      return *this;
    }

    /// Subtract @a s from this rational number.
    template<typename _Up>
    rational<_Z>& operator-=(const rational<_Up>& s)
    { 
      _num = _num * s.denom() - _denom * s.num(); 
      _denom *= s.denom();
      normalize();
      return *this;
    }

    /// Multiply @a s to this rational number.
    template<typename _Up>
    rational<_Z>& operator*=(const rational<_Up>& s)
    { 
      _num *= s.num(); 
      _denom *= s.denom();
      normalize();
      return *this;
    }

    /// Divide @a s to this rational number.
    template<typename _Up>
    rational<_Z>& operator/=(const rational<_Up>& s)
    {
      *this *= rational<_Z>(s.denom(), s.num());
      return *this;
    }

    /// Cast to double
    operator double () const { return double(num()) / denom(); }

  private:
    /// Normalize rational number.
    void normalize() { 
      if (_denom < _Z()) { 
	      _num = -_num; 
	      _denom = -_denom; 
      } 
      _Z g = gcd(_num, _denom);
      _num /= g;
      _denom /= g;
    }
    
  private:
    _Z _num;
    _Z _denom;
    
  };
  
  // Operators:
  ///  Return new rational number @a r plus @a s.
  template<typename _Z, typename _Up>
  inline auto
  operator+(const rational<_Z>& r, const rational<_Up>& s) 
    -> rational<decltype(r.num()*s.denom())>
  {
    auto num = r.num() * s.denom() + r.denom() * s.num(); 
    decltype(num) denom =  r.denom() * s.denom();
    return rational<decltype(num)> {num, denom}; 
  }

  ///  Return new rational number @a r plus @a s.
  template<typename _Z, typename _Up>
  inline auto
  operator-(const rational<_Z>& r, const rational<_Up>& s) 
    -> rational<decltype(r.denom()*s.denom())>
  {
    //auto num = r.num() * s.denom() - r.denom() * s.num(); 
    //decltype(num) denom =  r.denom() * s.denom();
    return rational<decltype(r.denom()*s.denom())> 
      { r.num() * s.denom() - r.denom() * s.num(),
	r.denom() * s.denom() }; 
  }

  ///  Return new rational number @a r times @a s.
  template<typename _Z, typename _Up>
  inline auto
  operator*(const rational<_Z>& r, const rational<_Up>& s)
    -> rational<decltype(r.num()*s.num())>
  {
    return rational<decltype(r.num()*s.num())> 
      { r.num()*s.num(), r.denom()*s.denom() };
  }
  
  ///  Return new rational number @a r times @a s.
  template<typename _Z, typename _Up>
  inline auto 
  operator/(const rational<_Z>& r, const rational<_Up>& s)
    -> decltype(r * s) 
  {
    return r * rational<_Up>(s.denom(), s.num());
  }
  
  //xxx ///  Return new rational number @a r minus @a s.
  //xxx template<typename _Z>
  //xxx inline rational<_Z>
  //xxx operator-(rational<_Z> r, const rational<_Z>& s) { return r -= s; }
  //xxx 
  //xxx //@{
  //xxx ///  Return new rational number @a r times @a a.
  //xxx template<typename _Z>
  //xxx inline rational<_Z>
  //xxx operator*(rational<_Z> r, const rational<_Z>& s) { return r *= s; }
  //xxx 
  //xxx template<typename _Z>
  //xxx inline rational<_Z>
  //xxx operator*(rational<_Z> r, const _Z& a) { return r *= a; }
  //xxx 
  //xxx template<typename _Z>
  //xxx inline rational<_Z>
  //xxx operator*(const _Z& a, rational<_Z> r) { return r *= a; }
  //xxx //@}
  //xxx 
  //xxx ///  Return new rational number @a r divided by @a a.
  //xxx template<typename _Z>
  //xxx inline rational<_Z>
  //xxx operator/(rational<_Z> r, const _Z& a) { return r /= a; }
  
  /// Return @a r.
  template<typename _Z>
  inline constexpr rational<_Z>
  operator+(const rational<_Z>& r) noexcept { return r; }

  /// Return negation of @a r
  template<typename _Z>
  inline constexpr rational<_Z>
  operator-(const rational<_Z>& r) noexcept
  { return rational<_Z>(-r.num(), r.denom()); }
  
  /// Return true if @a r is equal to @a s.
  template<typename _Z, typename _Up>
  inline bool
  operator==(const rational<_Z>& r, const rational<_Up>& s)
  { 
    assert(!(r.num() == 0 && r.denom() == 0)); // NaN
    assert(!(s.num() == 0 && s.denom() == 0)); // NaN
    return r.num() == s.num() && s.denom() == r.denom();
  }

  /// Return false if @a r is equal to @a s.
  template<typename _Z, typename _Up>
  inline constexpr bool
  operator!=(const rational<_Z>& r, const rational<_Up>& s) noexcept
  { return !(r == s); }

  /// Return true if @a r is less than @a s.
  template<typename _Z, typename _Up>
  inline constexpr bool
  operator<(const rational<_Z>& r, const rational<_Up>& s) noexcept
  { return r.num()*s.denom() < r.denom()*s.num(); }

  ///  Insertion operator for rational number values.
  template<typename _Z, class _Stream>
  _Stream& operator<<(_Stream& os, const rational<_Z>& r)
  {
    const auto& a = r.num();
    const auto& b = r.denom();
    _Z zero(0), one(1);
    if (b == one)  { os << a; return os; }
    if (b != zero) { os << '(' << a << '/' << b << ')'; return os; }
    if (a < zero)  { os << "-Inf"; return os; }
    if (a > zero)  { os << "Inf"; return os; }
    os << "NaN"; return os;
  }

}

#endif
