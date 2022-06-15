#pragma once

#include "matrix4.hpp"

namespace MyGL {
    Matrix4 lookAt(const double&, const double&,
                const double&, const double&,
                const double&, const double&,
                const double&, const double&,
                const double&);

    Matrix4 frustum(double, double, double,
                   double, double, double);
}
