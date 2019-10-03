#ifndef FUN_RAT_HPP
#define FUN_RAT_HPP

/**

- Modify from boost::rational<>
- Features:
  - No exception, support NaN, $\pm\Infty$.
  - Avoid normalization in every operation.
    Avoid gcd() in every operation to speed up the calculation.
    The rationale behind this is that: the comparsion (operator==)
    and printout are not often used.
  - Check 2/4 == 1/2

- Rule:
  1. check if den1 == den2 first

**/

#include <boost/config.hpp> // for BOOST_NO_STDC_NAMESPACE, BOOST_MSVC, etc
#ifndef BOOST_NO_IOSTREAM
#include <iomanip> // for std::setw
#include <ios>     // for std::noskipws, streamsize
#include <istream> // for std::istream
#include <ostream> // for std::ostream
#include <sstream> // for std::ostringstream
#endif
#include <cstddef> // for NULL
// xxx #include <stdexcept>             // for std::domain_error
#include <boost/assert.hpp>            // for BOOST_ASSERT
#include <boost/call_traits.hpp>       // for boost::call_traits
#include <boost/detail/workaround.hpp> // for BOOST_WORKAROUND
#include <boost/operators.hpp>         // for boost::addable etc
#include <cstdlib>                     // for std::abs
#include <string>                      // for std::string implicit constructor

//#include <boost/integer/common_factor_rt.hpp> // for boost::integer::gcd, lcm
#include <boost/static_assert.hpp> // for BOOST_STATIC_ASSERT
#include <limits>                  // for std::numeric_limits
#include <type_traits>             // is_integral<T>


// Control whether depreciated GCD and LCM functions are included (default: yes)
#ifndef BOOST_CONTROL_RATIONAL_HAS_GCD
#define BOOST_CONTROL_RATIONAL_HAS_GCD 1
#endif

namespace boost {

template <typename _Z,
          class = typename std::enable_if<std::is_integral<_Z>::value>::type>
inline constexpr _Z gcd(const _Z &a, const _Z &b) noexcept {
  return b == _Z(0) ? abs(a) : gcd(b, a % b);
}

template <typename IntType>
class rat
    : less_than_comparable<
          rat<IntType>,
          equality_comparable<
              rat<IntType>,
              less_than_comparable2<
                  rat<IntType>, IntType,
                  equality_comparable2<
                      rat<IntType>, IntType,
                      addable<
                          rat<IntType>,
                          subtractable<
                              rat<IntType>,
                              multipliable<
                                  rat<IntType>,
                                  dividable<
                                      rat<IntType>,
                                      addable2<
                                          rat<IntType>, IntType,
                                          subtractable2<
                                              rat<IntType>, IntType,
                                              subtractable2_left<
                                                  rat<IntType>, IntType,
                                                  multipliable2<
                                                      rat<IntType>, IntType,
                                                      dividable2<
                                                          rat<IntType>, IntType,
                                                          dividable2_left<
                                                              rat<IntType>,
                                                              IntType,
                                                              incrementable<
                                                                  rat<IntType>,
                                                                  decrementable<rat<
                                                                      IntType>>>>>>>>>>>>>>>>> {
  // Class-wide pre-conditions
  static_assert(::std::numeric_limits<IntType>::is_specialized);

  // Helper types
  typedef typename boost::call_traits<IntType>::param_type param_type;

  struct helper {
    IntType parts[2];
  };
  typedef IntType (helper::*bool_type)[2];

public:
  // Component type
  typedef IntType int_type;

  BOOST_CONSTEXPR
  rat() : num(0), den(1) {}
  BOOST_CONSTEXPR
  rat(param_type n) : num(n), den(1) {}
  rat(param_type n, param_type d) : num(n), den(d) { normalize(); }

#ifndef BOOST_NO_MEMBER_TEMPLATES
  template <typename NewType>
  BOOST_CONSTEXPR explicit rat(rat<NewType> const &r)
      : num(r.numerator()), den(r.denominator()) {}
#endif

  // Default copy constructor and assignment are fine

  // Add assignment from IntType
  rat &operator=(param_type i) {
    num = i;
    den = 1;
    return *this;
  }

  // Assign in place
  rat &assign(param_type n, param_type d);

  // Access to representation
  BOOST_CONSTEXPR
  IntType numerator() const { return num; }
  BOOST_CONSTEXPR
  IntType denominator() const { return den; }

  // Arithmetic assignment operators
  rat &operator+=(const rat &r);
  rat &operator-=(const rat &r);
  rat &operator*=(const rat &r);
  rat &operator/=(const rat &r);

  rat &operator+=(param_type i) {
    num += i * den;
    return *this;
  }
  rat &operator-=(param_type i) {
    num -= i * den;
    return *this;
  }
  rat &operator*=(param_type i);
  rat &operator/=(param_type i);

  // Increment and decrement
  const rat &operator++() {
    num += den;
    return *this;
  }
  const rat &operator--() {
    num -= den;
    return *this;
  }

  // Operator not
  BOOST_CONSTEXPR
  bool operator!() const { return !num; }

// Boolean conversion

#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003)
// The "ISO C++ Template Parser" option in CW 8.3 chokes on the
// following, hence we selectively disable that option for the
// offending memfun.
#pragma parse_mfunc_templ off
#endif

  BOOST_CONSTEXPR
  operator bool_type() const { return operator!() ? 0 : &helper::parts; }

#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003)
#pragma parse_mfunc_templ reset
#endif

  // Comparison operators
  bool operator<(const rat &r) const;
  BOOST_CONSTEXPR
  bool operator==(const rat &r) const;

  bool operator<(param_type i) const;
  bool operator>(param_type i) const;
  BOOST_CONSTEXPR
  bool operator==(param_type i) const;

private:
  // Implementation - numerator and denominator (normalized).
  // Other possibilities - separate whole-part, or sign, fields?
  IntType num;
  IntType den;

  // Helper functions
  static BOOST_CONSTEXPR int_type
  inner_gcd(param_type a, param_type b, int_type const &zero = int_type(0)) {
    return b == zero ? a : inner_gcd(b, a % b, zero);
  }

  static BOOST_CONSTEXPR int_type
  inner_abs(param_type x, int_type const &zero = int_type(0)) {
    return x < zero ? -x : +x;
  }

  // Representation note: Fractions are kept in normalized form at all
  // times. normalized form is defined as gcd(num,den) == 1 and den > 0.
  // In particular, note that the implementation of abs() below relies
  // on den always being positive.
  // bool test_invariant() const;
  void normalize();

  static BOOST_CONSTEXPR bool is_normalized(param_type n, param_type d,
                                            int_type const &zero = int_type(0),
                                            int_type const &one = int_type(1)) {
    return d >= zero;
  }
};

// Assign in place
template <typename IntType>
inline rat<IntType> &rat<IntType>::assign(param_type n, param_type d) {
  return *this = rat(n, d);
}

// Unary plus and minus
template <typename IntType>
BOOST_CONSTEXPR inline rat<IntType> operator+(const rat<IntType> &r) {
  return r;
}

template <typename IntType>
inline rat<IntType> operator-(const rat<IntType> &r) {
  return rat<IntType>(-r.numerator(), r.denominator());
}

// Arithmetic assignment operators
template <typename IntType>
rat<IntType> &rat<IntType>::operator+=(const rat<IntType> &r) {
  // This calculation avoids overflow, and minimises the number of expensive
  // calculations. Thanks to Nickolay Mladenov for this algorithm.
  //
  // Proof:
  // We have to compute a/b + c/d, where gcd(a,b)=1 and gcd(b,c)=1.
  // Let g = gcd(b,d), and b = b1*g, d=d1*g. Then gcd(b1,d1)=1
  //
  // The result is (a*d1 + c*b1) / (b1*d1*g).
  // Now we have to normalize this ratio.
  // Let's assume h | gcd((a*d1 + c*b1), (b1*d1*g)), and h > 1
  // If h | b1 then gcd(h,d1)=1 and hence h|(a*d1+c*b1) => h|a.
  // But since gcd(a,b1)=1 we have h=1.
  // Similarly h|d1 leads to h=1.
  // So we have that h | gcd((a*d1 + c*b1) , (b1*d1*g)) => h|g
  // Finally we have gcd((a*d1 + c*b1), (b1*d1*g)) = gcd((a*d1 + c*b1), g)
  // Which proves that instead of normalizing the result, it is better to
  // divide num and den by gcd((a*d1 + c*b1), g)

  // Protect against self-modification
  IntType r_num = r.num;
  IntType r_den = r.den;

  // Avoid repeated construction
  // IntType zero(0);

  if (den == r_den) {
    num += r_num;
    return *this;
  }

  IntType g = gcd(den, r_den);
  den /= g; // = b1 from the calculations above
  num = num * (r_den / g) + r_num * den;
  g = gcd(num, g);
  num /= g;
  den *= r_den / g;

  return *this;
}

template <typename IntType>
rat<IntType> &rat<IntType>::operator-=(const rat<IntType> &r) {
  // Protect against self-modification
  IntType r_num = r.num;
  IntType r_den = r.den;

  // Avoid repeated construction
  // IntType zero(0);

  if (den == r_den) {
    num -= r_num;
    return *this;
  }

  // This calculation avoids overflow, and minimises the number of expensive
  // calculations. It corresponds exactly to the += case above
  IntType g = gcd(den, r_den);
  den /= g;
  num = num * (r_den / g) - r_num * den;
  g = gcd(num, g);
  num /= g;
  den *= r_den / g;

  return *this;
}

template <typename IntType>
rat<IntType> &rat<IntType>::operator*=(const rat<IntType> &r) {
  // Protect against self-modification
  IntType r_num = r.num;
  IntType r_den = r.den;

  if (num == r_den) {
    num = r_num;
    return *this;
  }
  if (den == r_num) {
    den = r_den;
    return *this;
  }

  num *= r_num;
  den *= r_den;
  return *this;
}

template <typename IntType>
rat<IntType> &rat<IntType>::operator/=(const rat<IntType> &r) {
  // Protect against self-modification
  IntType r_num = r.num;
  IntType r_den = r.den;

  // Avoid repeated construction
  IntType zero(0);

  // Trap division by zero
  if (r_num == zero && num == zero) {
    den = zero;
    return *this;
  }
  if (r_den == zero && den == zero) {
    num = zero;
    return *this;
  }

  // Avoid overflow and preserve normalization
  IntType gcd1 = gcd(num, r_num);
  IntType gcd2 = gcd(r_den, den);
  num = (num / gcd1) * (r_den / gcd2);
  den = (den / gcd2) * (r_num / gcd1);

  if (den < zero) {
    num = -num;
    den = -den;
  }
  return *this;
}

// Mixed-mode operators
template <typename IntType>
inline rat<IntType> &rat<IntType>::operator*=(param_type i) {
  // Avoid repeated construction
  IntType zero(0);

  if (i == zero && den == zero) {
    num = zero;
    return *this;
  }

  // Avoid overflow and preserve normalization
  IntType gcd1 = gcd(i, den);
  num *= i / gcd1;
  den /= gcd1;

  return *this;
}

template <typename IntType>
rat<IntType> &rat<IntType>::operator/=(param_type i) {
  // Avoid repeated construction
  IntType const zero(0);

  if (i == zero && num == zero) {
    den = zero;
    return *this;
  }

  // Avoid overflow and preserve normalization
  IntType const gcd1 = gcd(num, i);
  num /= gcd1;
  den *= i / gcd1;

  if (den < zero) {
    num = -num;
    den = -den;
  }

  return *this;
}

// Comparison operators
template <typename IntType>
bool rat<IntType>::operator<(const rat<IntType> &r) const {
  if (den == r.den)
    return num < r.num;
  return num * r.den < den * r.num;
}

template <typename IntType> bool rat<IntType>::operator<(param_type i) const {
  return num < den * i;
}

template <typename IntType> bool rat<IntType>::operator>(param_type i) const {
  return operator==(i) ? false : !operator<(i);
}

template <typename IntType>
BOOST_CONSTEXPR inline bool is_NaN(const rat<IntType> &r) {
  // Avoid repeated construction
  IntType const zero(0);
  return r.denominator() == zero && r.numerator() == zero;
}

template <typename IntType>
BOOST_CONSTEXPR inline bool rat<IntType>::
operator==(const rat<IntType> &r) const {
  if (den == r.den)
    return num == r.num;
  return num * r.den == r.num * den;
}

template <typename IntType>
BOOST_CONSTEXPR inline bool rat<IntType>::operator==(param_type i) const {
  return num == i * den;
}

// Invariant check
// template <typename IntType>
// inline bool rat<IntType>::test_invariant() const
//{
//    if (this->den == int_type(0) ) return true;
//    return ( gcd(this->num, this->den) == int_type(1) );
//}

// Normalisation
template <typename IntType> void rat<IntType>::normalize() {
  // Avoid repeated construction
  IntType zero(0);

  if (den == zero)
    return;

  // Handle the case of zero separately, to avoid division by zero
  if (num == zero) {
    den = IntType(1);
    return;
  }

  IntType g = gcd(num, den);

  num /= g;
  den /= g;

  // Ensure that the denominator is positive
  if (den < zero) {
    num = -num;
    den = -den;
  }

  // ...But acknowledge that the previous step doesn't always work.
  // (Nominally, this should be done before the mutating steps, but this
  // member function is only called during the constructor, so we never have
  // to worry about zombie objects.)
  // if (den < zero)
  //     throw bad_rat( "bad rat: non-zero singular denominator" );

  // BOOST_ASSERT( this->test_invariant() );
}

#ifndef BOOST_NO_IOSTREAM
namespace detail {

// A utility class to reset the format flags for an istream at end
// of scope, even in case of exceptions
struct resetter {
  resetter(std::istream &is) : is_(is), f_(is.flags()) {}
  ~resetter() { is_.flags(f_); }
  std::istream &is_;
  std::istream::fmtflags f_; // old GNU c++ lib has no ios_base
};
}

// Input and output
template <typename IntType>
std::istream &operator>>(std::istream &is, rat<IntType> &r) {
  using std::ios;

  IntType n = IntType(0), d = IntType(1);
  char c = 0;
  detail::resetter sentry(is);

  if (is >> n) {
    if (is.get(c)) {
      if (c == '/') {
        if (is >> std::noskipws >> d)
          r.assign(n, d);
      } else
        is.setstate(ios::failbit);
    }
  }

  return is;
}

// Add manipulators for output format?
template <typename IntType>
std::ostream &operator<<(std::ostream &os, const rat<IntType> &r) {
  using namespace std;

  // The slash directly precedes the denominator, which has no prefixes.
  ostringstream ss;

  ss.copyfmt(os);
  ss.tie(NULL);
  ss.exceptions(ios::goodbit);
  ss.width(0);
  ss << noshowpos << noshowbase << '/' << r.denominator();

  // The numerator holds the showpos, internal, and showbase flags.
  string const tail = ss.str();
  streamsize const w = os.width() - static_cast<streamsize>(tail.size());

  ss.clear();
  ss.str("");
  ss.flags(os.flags());
  ss << setw(w < 0 || (os.flags() & ios::adjustfield) != ios::internal ? 0 : w)
     << r.numerator();
  return os << ss.str() + tail;
}
#endif // BOOST_NO_IOSTREAM

// Type conversion
template <typename T, typename IntType>
BOOST_CONSTEXPR inline T rat_cast(const rat<IntType> &src) {
  return static_cast<T>(src.numerator()) / static_cast<T>(src.denominator());
}

// Do not use any abs() defined on IntType - it isn't worth it, given the
// difficulties involved (Koenig lookup required, there may not *be* an abs()
// defined, etc etc).
template <typename IntType> inline rat<IntType> abs(const rat<IntType> &r) {
  return r.numerator() >= IntType(0) ? r : -r;
}

} // namespace boost

#endif // BOOST_RAT_HPP
