#ifndef _PROJ_XFORM_HPP
#define _PROJ_XFORM_HPP 1

// xxx #include "point3.hpp"
// xxx #include "line3.hpp"
#include "matrix3d.hpp"
#include "point2d.hpp"

namespace fun {

/// Create correcting perspective matrix
template <typename _Tp>
matrix3d<_Tp> correct_persp(const point2d<_Tp> &A, const point2d<_Tp> &B,
                            const point2d<_Tp> &C, const point2d<_Tp> &D);
}

#endif
