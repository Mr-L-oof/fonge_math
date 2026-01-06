#pragma once

#include "vector_float.hpp"

namespace fonge {

struct float3x3;
struct float4x4;

struct float2x2 {
    inline float2x2()
    : cols{float2(1, 0), float2(0, 1)} {}

    inline float2x2(float m11, float m21,
                float m12, float m22)
    : cols{float2(m11, m12), float2(m21, m22)} {}

    inline float2x2(float2 col1, float2 col2)
    : cols{col1, col2} {}

    inline float2x2(float4 numberVector) 
    : float2x2(numberVector.xy(), numberVector.wz()) {}

    inline float2x2(float3x3 rhs);

    inline float2x2(float4x4 rhs);

    inline float2x2 operator+(float2x2 rhs) {
        return float2x2(cols[0] + rhs.cols[0], cols[1] + rhs.cols[1]);
    }

    inline float2x2 operator-(float2x2 rhs) {
        return float2x2(col1 - rhs.col1, col2 - rhs.col2);
    }

    inline float2 operator*(float2 rhs) {
        return rhs.xx()*col1 + rhs.yy()*col2;
    }

    inline float2x2 operator*(float2x2 rhs) {
        return float2x2((*this) * rhs.col1, (*this) * rhs.col2);
    }

    inline float2 &operator[](size_t i) {
        return cols[i];
    }

    inline bool operator==(float2x2 rhs) {
        return (col1 == rhs.col1).all() && (col2 == rhs.col2).all();
    }

    inline float2x2 transposed() {
        return float2x2(float4(simde_mm_unpacklo_ps(col1.simd, col2.simd)));
    }

    inline float trace() {
        return col1.x() + col2.y();
    }

    inline float determinant() {
        return col1.dot(col2.cross());
    }

    inline float2x2 cofactor() {
        return float2x2(col2.cross(), -col1.cross());
    }
    inline float2x2 operator/(float rhs) {
        return float2x2(col1/rhs, col2/rhs);
    }
    inline float2x2 inverse() {
        return cofactor().transposed()/determinant();
    }

    static inline float2x2 identity() {
        return float2x2();
    }

    union {
        float2 cols[2];
        
        struct {
            float2 col1, col2;
        };
    };
};

inline float2 operator*(float2 lhs, float2x2 rhs) {
    return float2(lhs.dot(rhs.col1), lhs.dot(rhs.col2));
}

inline float2x2 operator*(float2x2 lhs, float rhs) {
    return float2x2(lhs.col1*rhs, lhs.col2*rhs);
}

inline float2x2 operator*(float lhs, float2x2 rhs) {
    return operator*(rhs, lhs);
}



struct float3x3 {
    inline float3x3()
    : cols{float3(1, 0, 0), float3(0, 1, 0), float3(0, 0, 1)} {}

    inline float3x3(float m11, float m21, float m31,
                    float m12, float m22, float m32,
                    float m13, float m23, float m33)
                    : col1(m11, m12, m13), col2(m21, m22, m23), col3(m31, m32, m33)  {}
    
    inline float3x3(float3 col1, float3 col2, float3 col3)
    : cols{col1, col2, col3} {}

    inline float3x3(float4x4 rhs);

    inline float3x3 operator+(float3x3 rhs) {
        return float3x3(col1 + rhs.col1, col2 + rhs.col2, col3 + rhs.col3);
    }

    inline float3x3 operator-(float3x3 rhs) {
        return float3x3(col1 - rhs.col1, col2 - rhs.col2, col3 - rhs.col3);
    }

    inline float3 operator*(float3 rhs) {
        return rhs.xxx()*col1 + rhs.yyy()*col2 + rhs.zzz()*col3;
    }

    inline float3x3 operator*(float3x3 rhs) {
        return float3x3((*this)*rhs.col1, (*this)*rhs.col2,(*this)*rhs.col3);
    }

    inline float3 &operator[](size_t i) {
        return cols[i];
    }

    inline bool operator==(float3x3 rhs) {
        return (col1 == rhs.col1).all() && (col2 == rhs.col2).all() && (col3 == rhs.col3).all();
    }

    inline float3x3 transposed() {
        simde__m128 a = col1.simd, b = col2.simd, c = col3.simd, d = simde_mm_setzero_ps();
        SIMDE_MM_TRANSPOSE4_PS(a, b, c, d);
        return float3x3(a, b, c);
    }

    inline float trace() {
        return col1.x() + col2.y() + col3.z();
    }

    inline float determinant() {
        return col1.dot(col2.cross(col3));
    }

    inline float3x3 cofactor() {
        return float3x3(col2.cross(col3), col3.cross(col1), col1.cross(col2));
    }

    inline float3x3 operator/(float rhs) {
        return float3x3(col1/rhs, col2/rhs, col3/rhs);
    }

    inline float3x3 inverse() {
        return cofactor().transposed()/determinant();
    }

    static inline float3x3 identity() {
        return float3x3();
    }

    union {
        float3 cols[3];

        struct {
            float3 col1, col2, col3;
        };
    };
    
};

inline float3 operator*(float3 lhs, float3x3 rhs) {
    return float3(lhs.dot(rhs.col1), lhs.dot(rhs.col2), lhs.dot(rhs.col3));
}

inline float3x3 operator*(float3x3 lhs, float rhs) {
    return float3x3(lhs.col1 * rhs, lhs.col2 * rhs, lhs.col3 * rhs);
}

inline float3x3 operator*(float lhs, float3x3 rhs) {
    return operator*(rhs, lhs);
}

inline float2x2::float2x2(float3x3 rhs) {
    col1 = rhs.col1.xy();
    col2 = rhs.col2.xy();
}

struct float4x4 {
    inline float4x4(const float4x4 &m) 
    : col1(m.col1), col2(m.col2), col3(m.col3), col4(m.col4) {};

    inline float4x4()
    : cols{float4(1, 0, 0, 0), float4(0, 1, 0, 0), float4(0, 0, 1, 0), float4(0, 0, 0, 1)} {}

    inline float4x4(float m11, float m21, float m31, float m41,
                    float m12, float m22, float m32, float m42,
                    float m13, float m23, float m33, float m43,
                    float m14, float m24, float m34, float m44)
                    : col1(m11, m12, m13, m14), col2(m21, m22, m23, m24), col3(m31, m32, m33, m34), col4(m14, m24, m34, m44) {}
    
    inline float4x4(float4 col1, float4 col2, float4 col3, float4 col4)
    : cols{col1, col2, col3, col4} {}

    inline float4x4 operator+(float4x4 rhs) {
        return float4x4(col1 + rhs.col1, col2 + rhs.col2, col3 + rhs.col3, col4 + rhs.col4);
    }

    inline float4x4 operator-(float4x4 rhs) {
        return float4x4(col1 - rhs.col1, col2 - rhs.col2, col3 - rhs.col3, col4 - rhs.col4);
    }

    inline float4 operator*(float4 rhs) {
        return rhs.xxxx()*col1 + rhs.yyyy()*col2 + rhs.zzzz()*col3 + rhs.wwww()*col4;
    }

    inline float4x4 operator*(float4x4 rhs) {
        return float4x4((*this)*rhs.col1, (*this)*rhs.col2,(*this)*rhs.col3, (*this)*rhs.col4);
    }

    inline float4 &operator[](size_t i) {
        return cols[i];
    }

    inline bool operator==(float4x4 rhs) {
        return (col1 == rhs.col1).all() && (col2 == rhs.col2).all() && (col3 == rhs.col3).all() && (col4 == rhs.col4).all();
    }

    inline float4x4 transposed() {
        simde__m128 a = col1.simd, b = col2.simd, c = col3.simd, d = col4.simd;
        SIMDE_MM_TRANSPOSE4_PS(a, b, c, d);
        return float4x4(a, b, c, d);
    }

    inline float trace() {
        return col1.x() + col2.y() + col3.z() + col4.w();
    }

    inline float determinant() {
        return col1.dot(col2.cross(col3, col4));
    }

    inline float4x4 cofactor() {
        return float4x4(col2.cross(col3, col4), col1.cross(col3, col2), col1.cross(col2, col4), col2.cross(col1, col3));
    }

    inline float4x4 operator/(float rhs) {
        return float4x4(col1/rhs, col2/rhs, col3/rhs, col4/rhs);
    }

    inline float4x4 inverse() {
        return cofactor().transposed()/determinant();
    }

    static inline float4x4 identity() {
        return float4x4();
    }

    union {
        float4 cols[4];

        struct {
            float4 col1, col2, col3, col4;
        };
    };
    
};

inline float4 operator*(float4 lhs, float4x4 rhs) {
    return float4(lhs.dot(rhs.col1), lhs.dot(rhs.col2), lhs.dot(rhs.col3), lhs.dot(rhs.col4));
}

inline float4x4 operator*(float4x4 lhs, float rhs) {
    return float4x4(lhs.col1 * rhs, lhs.col2 * rhs, lhs.col3 * rhs, lhs.col4 * rhs);
}

inline float4x4 operator*(float lhs, float4x4 rhs) {
    return operator*(rhs, lhs);
}

inline float2x2::float2x2(float4x4 rhs) {
    col1 = rhs.col1.xy();
    col2 = rhs.col2.xy();
}

inline float3x3::float3x3(float4x4 rhs) {
    col1 = rhs.col1.xyz();
    col2 = rhs.col2.xyz();
    col3 = rhs.col3.xyz();
}

}
