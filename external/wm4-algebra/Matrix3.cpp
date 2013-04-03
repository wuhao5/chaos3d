// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#include "Matrix3.h"

namespace Wm4{

template<> const Matrix3<float> Matrix3<float>::ZERO(
    0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f);
template<> const Matrix3<float> Matrix3<float>::IDENTITY(
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f);

template<> const Matrix3<double> Matrix3<double>::ZERO(
    0.0,0.0,0.0,
    0.0,0.0,0.0,
    0.0,0.0,0.0);
template<> const Matrix3<double> Matrix3<double>::IDENTITY(
    1.0,0.0,0.0,
    0.0,1.0,0.0,
    0.0,0.0,1.0);

template class Matrix3<float>;
    
}