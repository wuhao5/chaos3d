// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#include "Vector2.h"

namespace Wm4{

template class Vector2<float>;

template<> const Vector2<float> Vector2<float>::ZERO(0.0f,0.0f);
template<> const Vector2<float> Vector2<float>::UNIT_X(1.0f,0.0f);
template<> const Vector2<float> Vector2<float>::UNIT_Y(0.0f,1.0f);
template<> const Vector2<float> Vector2<float>::ONE(1.0f,1.0f);

template<> const Vector2<double> Vector2<double>::ZERO(0.0,0.0);
template<> const Vector2<double> Vector2<double>::UNIT_X(1.0,0.0);
template<> const Vector2<double> Vector2<double>::UNIT_Y(0.0,1.0);
template<> const Vector2<double> Vector2<double>::ONE(1.0,1.0);

}