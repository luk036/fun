//  rational number example program  ----------------------------------------//

//  (C) Copyright Paul Moore 1999. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright notice
//  appears in all copies. This software is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.

// boostinspect:nolicense (don't complain about the lack of a Boost license)
// (Paul Moore hasn't been in contact for years, so there's no way to change the
// license.)

//  Revision History
//  14 Dec 99  Initial version

#include "rat.hpp"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <boost/config.hpp>
#ifndef BOOST_NO_LIMITS
#include <limits>
#else
#include <limits.h>
#endif
#include <exception>
//#include <boost/rational.hpp>

using std::cout;
using std::endl;
using boost::rat;

#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
// This is a nasty hack, required because MSVC does not implement "Koenig
// Lookup". Basically, if I call abs(r), the C++ standard says that the
// compiler should look for a definition of abs in the namespace which
// contains r's class (in this case boost) - among other places.

// Koenig Lookup is a relatively recent feature, and other compilers may not
// implement it yet. If so, try including this line.

using boost::abs;
#endif

int main ()
{
    rat<int> half(1,2);
    rat<int> one(1);
    rat<int> two(2);
    rat<int> infty(1,0);
    rat<int> ninfty(-1,0);
    rat<int> zero(0,1);
    rat<int> nan(0,0);

    // Some basic checks
    assert(half.numerator() == 1);
    assert(half.denominator() == 2);
    assert(boost::rat_cast<double>(half) == 0.5);

    // Arithmetic
    assert(half + half == one);
    assert(one - half == half);
    assert(two * half == one);
    assert(one / half == two);
    
    assert(half + infty == infty);
    assert(half - infty == ninfty);
    assert(half * infty == infty);
    assert(half / infty == zero);
    assert(infty / half == infty);

    assert(half + ninfty == ninfty);
    assert(half - ninfty == infty);
    assert(half * ninfty == ninfty);
    assert(half / ninfty == zero);
    assert(ninfty / half == ninfty);

    //assert(infty + infty == infty);
    //assert(is_NaN(infty - infty));
    //assert(infty * infty == infty);
    assert(is_NaN(infty / infty));
    
    //assert(ninfty + ninfty == ninfty);
    //assert(is_NaN(ninfty - ninfty));
    //assert(ninfty * ninfty == infty);
    assert(is_NaN(ninfty / ninfty));

    assert(ninfty != infty);
    assert(zero + infty == infty);
    assert(zero - infty == ninfty);
    //assert(is_NaN(zero * infty));
    assert(zero / infty == zero);
    assert(infty / zero == infty);
    
    assert(zero + ninfty == ninfty);
    assert(zero - ninfty == infty);
    //assert(is_NaN(zero * ninfty));
    assert(zero / ninfty == zero);
    assert(ninfty / zero == ninfty);

    assert(is_NaN(nan + nan));
    assert(is_NaN(nan - nan));
    assert(is_NaN(nan * nan));
    assert(is_NaN(nan / nan));

    assert(half < infty);
    assert(ninfty < half);
    assert(ninfty < infty);

    
    // With conversions to integer
    assert(half+half == 1);
    assert(2 * half == one);
    assert(2 * half == 1);
    assert(one / half == 2);
    assert(1 / half == 2);

    assert(1 + infty == infty);
    assert(1 - infty == ninfty);
    assert(2 * infty == infty);
    assert(2 / infty == zero);
    

    // Sign handling
    rat<int> minus_half(-1,2);
    assert(-half == minus_half);
    assert(abs(minus_half) == half);

    // Do we avoid overflow?
#ifndef BOOST_NO_LIMITS
    int maxint = (std::numeric_limits<int>::max)();
#else
    int maxint = INT_MAX;
#endif
    rat<int> big(maxint, 2);
    assert(2 * big == maxint);

    // Print some of the above results
    cout << half << "+" << half << "=" << one << endl;
    cout << one << "-" << half << "=" << half << endl;
    cout << two << "*" << half << "=" << one << endl;
    cout << one << "/" << half << "=" << two << endl;
    cout << "abs(" << minus_half << ")=" << half << endl;
    cout << "2 * " << big << "=" << maxint
         << " (rat: " << rat<int>(maxint) << ")" << endl;

    // Some extras
    rat<int> pi(22,7);
    cout << "pi = " << boost::rat_cast<double>(pi) << " (nearly)" << endl;

    return 0;
}
