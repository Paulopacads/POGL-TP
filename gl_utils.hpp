#pragma once

#include "matrix4.hpp"

namespace MyGL {
    Matrix4 lookAt(const float&, const float&,
                   const float&, const float&,
                   const float&, const float&,
                   const float&, const float&,
                   const float&);

    Matrix4 frustum(float, float, float,
                    float, float, float);
}
