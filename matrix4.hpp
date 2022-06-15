#pragma once

#include <stdlib.h>
#include <ostream>

namespace MyGL {
    class Matrix4 {
    public:
        Matrix4();
        Matrix4(const double[16]);
        void operator*=(const Matrix4&);
        double operator[](const size_t) const;
        double& operator[](const size_t);
        double *get_ptr();

        static Matrix4 identity() {
            Matrix4 mat = Matrix4();
            mat[0] = mat[5] = mat[10] = mat[15] = 1;
            return mat;
        }

    private:
        double _content[16] = { 0 };
    };
};

std::ostream& operator<<(std::ostream&, const MyGL::Matrix4&);
