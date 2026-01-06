#pragma once

#include <simde/x86/avx512.h>
#include "vector_double.hpp"

namespace fonge {

struct double2x2;
struct double3x3;
struct double4x4;

inline double2x2 operator*(double2x2 lhs, double rhs);

struct double2x2 {
    inline double2x2()
    : cols{double2(1, 0), double2(0, 1)} {}

    inline double2x2(double m11, double m21,
                double m12, double m22)
    : cols{double2(m11, m12), double2(m21, m22)} {}

    inline double2x2(double2 col1, double2 col2)
    : cols{col1, col2} {}

    inline double2x2(double3x3 rhs);

    inline double2x2(double4x4 rhs);

    inline double2x2 operator+(double2x2 rhs) {
        return double2x2(cols[0] + rhs.cols[0], cols[1] + rhs.cols[1]);
    }

    inline double2x2 operator-(double2x2 rhs) {
        return double2x2(col1 - rhs.col1, col2 - rhs.col2);
    }

    inline double2 operator*(double2 rhs) {
        return rhs.xx()*col1 + rhs.yy()*col2;
    }

    inline double2x2 operator*(double2x2 rhs) {
        return double2x2((*this) * rhs.col1, (*this) * rhs.col2);
    }

    inline double2 &operator[](size_t i) {
        return cols[i];
    }

    inline bool operator==(double2x2 rhs) {
        return (col1 == rhs.col1).all() && (col2 == rhs.col2).all();
    }

    inline double2x2 transposed() {
        double4 tmp = simde_mm256_unpacklo_pd(col1.simd, col2.simd);
        return double2x2(tmp.xy(), tmp.zw());
    }

    inline double trace() {
        return col1.x() + col2.y();
    }

    inline double determinant() {
        return col1.dot(col2.cross());
    }

    inline double2x2 cofactor() {
        return double2x2(col2.cross(), -col1.cross());
    }

    inline double2x2 inverse() {
        return (cofactor().transposed()) * (1/determinant());
    }

    static inline double2x2 identity() {
        return double2x2();
    }

    union {
        double2 cols[2];
        
        struct {
            double2 col1, col2;
        };
    };
};

inline double2 operator*(double2 lhs, double2x2 rhs) {
    return rhs.transposed() * lhs;
}

inline double2x2 operator*(double2x2 lhs, double rhs) {
    return double2x2(lhs.col1*rhs, lhs.col2*rhs);
}

inline double2x2 operator*(double lhs, double2x2 rhs) {
    return operator*(rhs, lhs);
}

inline double2x2 operator/(double2x2 lhs, double rhs) {
    return operator*(lhs, 1/rhs);
}

struct double3x3 {
    inline double3x3()
    : cols{double3(1, 0, 0), double3(0, 1, 0), double3(0, 0, 1)} {}

    inline double3x3(double m11, double m21, double m31,
                    double m12, double m22, double m32,
                    double m13, double m23, double m33)
                    : col1(m11, m12, m13), col2(m21, m22, m23), col3(m31, m32, m33)  {}
    
    inline double3x3(double3 col1, double3 col2, double3 col3)
    : cols{col1, col2, col3} {}

    inline double3x3(double4x4 rhs);

    inline double3x3 operator+(double3x3 rhs) {
        return double3x3(col1 + rhs.col1, col2 + rhs.col2, col3 + rhs.col3);
    }

    inline double3x3 operator-(double3x3 rhs) {
        return double3x3(col1 - rhs.col1, col2 - rhs.col2, col3 - rhs.col3);
    }

    inline double3 operator*(double3 rhs) {
        return rhs.xxx()*col1 + rhs.yyy()*col2 + rhs.zzz()*col3;
    }

    inline double3x3 operator*(double3x3 rhs) {
        return double3x3((*this)*rhs.col1, (*this)*rhs.col2,(*this)*rhs.col3);
    }

    inline double3 &operator[](size_t i) {
        return cols[i];
    }

    inline bool operator==(double3x3 rhs) {
        return (col1 == rhs.col1).all() && (col2 == rhs.col2).all() && (col3 == rhs.col3).all();
    }

    inline double3x3 transposed() {
        // top-left minor, already transposed I think.
        double4 tmp1 = simde_mm256_unpacklo_pd(col1.simd, col2.simd);
        // bottom-left minor.
        double2 tmp2 = simde_mm256_unpackhi_pd(col1.simd, col2.simd);
        return double3x3(double3(tmp1.xy(), col3.x()), double3(tmp1.zw(), col3.y()), double3(tmp2, col3.z()));
    }

    inline double trace() {
        return col1.x() + col2.y() + col3.z();
    }

    inline double determinant() {
        return col1.dot(col2.cross(col3));
    }

    inline double3x3 cofactor() {
        return double3x3(col2.cross(col3), col3.cross(col1), col1.cross(col2));
    }

    inline double3x3 operator/(double rhs) {
        return double3x3(col1/rhs, col2/rhs, col3/rhs);
    }

    inline double3x3 inverse() {
        return cofactor().transposed()/determinant();
    }

    static inline double3x3 identity() {
        return double3x3();
    }

    union {
        double3 cols[3];

        struct {
            double3 col1, col2, col3;
        };
    };
    
};

inline double3 operator*(double3 lhs, double3x3 rhs) {
    return rhs.transposed() * lhs;
}

inline double3x3 operator*(double3x3 lhs, double rhs) {
    return double3x3(lhs.col1 * rhs, lhs.col2 * rhs, lhs.col3 * rhs);
}

inline double3x3 operator*(double lhs, double3x3 rhs) {
    return operator*(rhs, lhs);
}

inline double2x2::double2x2(double3x3 rhs) {
    col1 = rhs.col1.xy();
    col2 = rhs.col2.xy();
}

struct double4x4 {
    inline double4x4(const double4x4 &m) 
    : cols{m.col1, m.col2, m.col3, m.col4} {};

    inline double4x4()
    : cols{double4(1, 0, 0, 0), double4(0, 1, 0, 0), double4(0, 0, 1, 0), double4(0, 0, 0, 1)} {}

    inline double4x4(double m11, double m21, double m31, double m41,
                    double m12, double m22, double m32, double m42,
                    double m13, double m23, double m33, double m43,
                    double m14, double m24, double m34, double m44)
                    : col1(m11, m12, m13, m14), col2(m21, m22, m23, m24), col3(m31, m32, m33, m34), col4(m14, m24, m34, m44) {}
    
    inline double4x4(double4 col1, double4 col2, double4 col3, double4 col4)
    : cols{col1, col2, col3, col4} {}

    inline double4x4 operator+(double4x4 rhs) {
        return double4x4(col1 + rhs.col1, col2 + rhs.col2, col3 + rhs.col3, col4 + rhs.col4);
    }

    inline double4x4 operator-(double4x4 rhs) {
        return double4x4(col1 - rhs.col1, col2 - rhs.col2, col3 - rhs.col3, col4 - rhs.col4);
    }

    inline double4 operator*(double4 rhs) {
        return rhs.xxxx()*col1 + rhs.yyyy()*col2 + rhs.zzzz()*col3 + rhs.wwww()*col4;
    }

    inline double4x4 operator*(double4x4 rhs) {
        return double4x4((*this)*rhs.col1, (*this)*rhs.col2,(*this)*rhs.col3, (*this)*rhs.col4);
    }

    inline double4 &operator[](size_t i) {
        return cols[i];
    }

    inline bool operator==(double4x4 rhs) {
        return (col1 == rhs.col1).all() && (col2 == rhs.col2).all() && (col3 == rhs.col3).all() && (col4 == rhs.col4).all();
    }

    inline double4x4 transposed() {
        double4x4 out;
        // top-left minor, already transposed.
        double4 tmp1 = simde_mm256_unpacklo_pd(col1.simd, col2.simd);
        // top-right minor, already transposed.
        double4 tmp2 = simde_mm256_unpacklo_pd(col3.simd, col4.simd);
        // bottom-left minor, already transposed.
        double4 tmp3 = simde_mm256_unpackhi_pd(col1.simd, col2.simd);
        // bottom-right minor, already transposed.
        double4 tmp4 = simde_mm256_unpackhi_pd(col3.simd, col4.simd);
        out.col1 = double4(tmp1.xy(), tmp3.xy());
        out.col2 = double4(tmp1.zw(), tmp3.zw());
        out.col3 = double4(tmp2.xy(), tmp4.xy());
        out.col4 = double4(tmp2.zw(), tmp4.zw());
        return out;
    }

    inline double trace() {
        return col1.x() + col2.y() + col3.z() + col4.w();
    }

    inline double determinant() {
        return col1.dot(col2.cross(col3, col4));
    }

    inline double4x4 cofactor() {
        return double4x4(col2.cross(col3, col4), col1.cross(col3, col2), col1.cross(col2, col4), col2.cross(col1, col3));
    }

    inline double4x4 operator/(double rhs) {
        return double4x4(col1/rhs, col2/rhs, col3/rhs, col4/rhs);
    }
    
    inline double4x4 inverse() {
        return cofactor().transposed()/determinant();
    }

    static inline double4x4 identity() {
        return double4x4();
    }

    union {
        double4 cols[4];

        struct {
            double4 col1, col2, col3, col4;
        };
    };
    
};

inline double4 operator*(double4 lhs, double4x4 rhs) {
    return rhs.transposed() * lhs;
}

inline double4x4 operator*(double4x4 lhs, double rhs) {
    return double4x4(lhs.col1 * rhs, lhs.col2 * rhs, lhs.col3 * rhs, lhs.col4 * rhs);
}

inline double4x4 operator*(double lhs, double4x4 rhs) {
    return operator*(rhs, lhs);
}

inline double2x2::double2x2(double4x4 rhs) {
    col1 = rhs.col1.xy();
    col2 = rhs.col2.xy();
}

inline double3x3::double3x3(double4x4 rhs) {
    col1 = rhs.col1.xyz();
    col2 = rhs.col2.xyz();
    col3 = rhs.col3.xyz();
}

}

