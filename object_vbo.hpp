#pragma once

#include <vector>

#include "matrix4.hpp"

static const std::vector<float> vertex_buffer_data {
    0, 2, 1,
    2, 1, 0,
    1, 0, 2,

    0, 2, 1,
    2, 0, 1,
    1, 0, 2,

    0, 2, 1,
    2, 1, 0,
    2, 0, 1,

    2, 1, 0,
    1, 0, 2,
    2, 0, 1
};

const float wc_array[16] = {
    0.6, -0.3, 0.6, 0.,
    0., 0.6, 0.6, 0.,
    -0.6, -0.3, 0.6, 0.,
    0., 0., -17, 1.
};

const float p_array[16] = {
    5., 0., 0., 0.,
    0., 5., 0., 0.,
    0., 0., -1., -1.,
    0., 0., -10., 0.
};
