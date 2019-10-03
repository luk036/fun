// The template and inlines for the -*- C++ -*- cyclic line classes.
// Initially implemented by Wai-Shing Luk <luk036@gmail.com>
//

/** @file include/cline.hpp
 *  This is a C++ Library header.
 */

#ifndef FUN_CLINE_HPP
#define FUN_CLINE_HPP 1

#include <cassert>
#include <sstream>
//#include <cpoint.hpp>

namespace fun {
// Forward declarations.
class cline;

/**
 *  Projective point represented by cyclic difference set
 *
 *  @param  Tp  Type of point elements
 */
class cpoint {
public:
  typedef cline dual;

  /// Default constructor.
  constexpr cpoint() : _m{0} {}

  constexpr cpoint(unsigned int m) : _m{m} {}

  /// Construct by meet of two lines @a p and @a q
  inline cpoint(const cline &p, const cline &q);

  /// Return true if a point @a p incident with this line
  inline bool incident(const cline &l) const;

  /// Return internal value
  constexpr unsigned int value() const { return _m; }

  // Lets the compiler synthesize the assignment operator
  // cpoint& operator= (const cpoint&);

private:
  unsigned int _m;
};

/**
 * @defgroup cyclic line
 * @ingroup geometry
 *
 * Classes and functions for cyclic line.
 * @{
 */

/**
 *  Projective line represented by cyclic difference set
 *
 *  @param  Tp  Type of line elements
 */
class cline {
public:
  typedef cpoint dual;

  /// Default constructor.
  constexpr cline() : _m{0} {}

  constexpr cline(unsigned int m) : _m{m} {}

  /// Construct by join of two points @a p and @a q
  inline cline(const cpoint &p, const cpoint &q);

  /// Return internal value
  constexpr unsigned int value() const noexcept { return _m; }

  // Lets the compiler synthesize the assignment operator
  // cline& operator= (const cline&);

  /// Return true if a point @a p incident with this line
  bool incident(const cpoint &p) const {
    for (auto q : {0, 1, 3, 9}) {
      if ((value() + q) % 13 == p.value())
        return true;
    }
    // xxx static const unsigned int _quorum[4] = { 0, 1, 3, 9 };
    // xxx for (unsigned int i=0; i<4; ++i)
    // xxx 	if ((value() + _quorum[i]) % 13 == p.value())
    // xxx 	  return true;
    return false;
  }

private:
  unsigned int _m;
};

// Operators:
/// Return true if @a p is equal to @a q (in 3d affine sense).
inline constexpr bool operator==(const cpoint &p, const cpoint &q) noexcept {
  return p.value() == q.value();
}

/// Return true if @a p is equivalent to @a q (in projective sense).
inline constexpr bool equiv(const cpoint &p, const cpoint &q) noexcept {
  return p == q;
}

/// Return false if @a p is equal to @a q.
inline constexpr bool operator!=(const cpoint &p, const cpoint &q) noexcept {
  return !(p == q);
}

/// Return true if a point @a p incident with a line @a l
// xxx inline bool incident(const cpoint& p, const cline& l)
// xxx {
// xxx   for (auto q : { 0,1,3,9 }) {
// xxx     if ((l.value() + q) % 13 == p.value())
// xxx 	return true;
// xxx   }
// xxx   return false;
// xxx }
// xxx
// xxx /// Return true if a point @a p incident with a line @a l
// xxx inline bool incident(const cline& l, const cpoint& p)
// xxx {
// xxx   return incident(p, l);
// xxx }

///  Return new line join @a p and @a q
inline cline::cline(const cpoint &p, const cpoint &q) {
  assert(p != q);
  static const unsigned int _M[13] = {100, 0, 1, 0, 9, 9, 3, 9, 1, 0, 3, 3, 1};
  unsigned int i = (q.value() + 13 - p.value()) % 13;
  _m = (p.value() + 13 - _M[i]) % 13;
}

/// Return incident of @a l and @a p
inline bool cpoint::incident(const cline &l) const { return l.incident(*this); }

/// Return incident of @a l and @a p
inline bool incident(const cpoint &p, const cline &l) { return l.incident(p); }

///  Return new line join @a p and @a q
inline cline join(const cpoint &p, const cpoint &q) { return cline{p, q}; }

///  Insertion operator for point values.
template <class _Stream> _Stream &operator<<(_Stream &os, const cpoint &p) {
  os << '{' << p.value() << '}';
  return os;
}

// Operators:
/// Return true if @a l is equal to @a m (in 3d affine sense).
inline constexpr bool operator==(const cline &l, const cline &m) noexcept {
  return l.value() == m.value();
}

/// Return true if @a l is equivalent to @a m (in projective sense).
inline constexpr bool equiv(const cline &l, const cline &m) noexcept {
  return l == m;
}

/// Return false if @a l is equal to @a m.
inline constexpr bool operator!=(const cline &l, const cline &m) noexcept {
  return !(l == m);
}

///  Return new point meet @a l and @a m (p. 53)
inline cpoint::cpoint(const cline &l, const cline &m) {
  assert(l != m);
  static unsigned int _M[13] = {100, 1, 3, 3, 0, 1, 9, 3, 9, 9, 0, 1, 0};
  auto i = (m.value() + 13 - l.value()) % 13;
  _m = (_M[i] + l.value()) % 13;
}

///  Return new point meet @a l and @a m (p. 53)
inline cpoint meet(const cline &l, const cline &m) { return cpoint{l, m}; }

///  Return determinant of @a l, @a m, @a n
// xxx template<typename _K>
// xxx inline _K
// xxx det(const cline& l, const cline& m, const cline& n)
// xxx { return det(l, m, n); }

///  Return true if @a l, @a m, @a n are concurrent
// xxx inline bool
// xxx concurrent(const cline& l, const cline& m, const cline& n)
// xxx { return l.incident(meet(m,n)); }

/// Return a line parallel to @a l and through @a p (p. 55)
// xxx template <typename _K>
// xxx inline cline parallel(const cpoint& p, const cline& l,
// xxx 			const cline& l_Inf = cline(0))
// xxx { return join(p, meet(l, l_Inf)); }

///  Insertion operator for line values.
template <class _Stream> _Stream &operator<<(_Stream &os, const cline &l) {
  os << "{ ";
  for (auto q : {0, 1, 3, 9}) {
    os << (l.value() + q) % 13 << ' ';
  }
  os << '}';
  return os;
}

} // namespace fun

#endif
