#include "matrix4.hpp"

namespace MyGL {
    Matrix4::Matrix4() {}

    Matrix4::Matrix4(const float content[16]) {
        for (size_t i = 0; i < 16; ++i)
            _content[i] = content[i];
    }

    void Matrix4::operator*=(const Matrix4& rhs) {
        float tmp[4] = { 0 };
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j)
                for (size_t k = 0; k < 4; ++k)
                    tmp[j] += _content[i * 4 + k] * rhs[k * 4 + j];

            for (size_t j = 0; j < 4; ++j)
                _content[i * 4 + j] = tmp[j];
        }
    }

    float Matrix4::operator[](const size_t i) const {
        return _content[i];
    }

    float& Matrix4::operator[](const size_t i) {
        return _content[i];
    }

    float *Matrix4::get_ptr() {
        return _content;
    }
}

std::ostream& operator<<(std::ostream& out, const MyGL::Matrix4& mat) {
    out << "Matrix: {\n"
        << mat[0]  << ' ' << mat[1]  << ' ' << mat[2]  << ' ' << mat[3]  << '\n'
        << mat[4]  << ' ' << mat[5]  << ' ' << mat[6]  << ' ' << mat[7]  << '\n'
        << mat[8]  << ' ' << mat[9]  << ' ' << mat[10] << ' ' << mat[11] << '\n'
        << mat[12] << ' ' << mat[13] << ' ' << mat[14] << ' ' << mat[15] << '\n'
        << '}';
    return out;
}
