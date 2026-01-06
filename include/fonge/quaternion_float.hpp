#include "matrix_float.hpp"
#include "vector_float.hpp"
#include <cmath>

namespace fonge {

struct quat {
    inline quat(float4 a)
    : vec(a) {}

    inline quat()
    : vec(0, 0, 0, 1) {}

    inline quat(float3 complex_part, float real_part) 
    : vec(complex_part, real_part) {}

    static inline quat from_angle_axis(float angle, float3 axis) {
        return float4(axis * sinf(angle/2), cosf(angle/2));
    }

    static inline quat from_cosangle_axis(float cosangle, float3 axis) {
        return float4(axis * sqrt(1-cosangle*cosangle),cosangle);
    }

    static inline quat from_euler_zxy(float pitch, float yaw, float roll) {
        return from_angle_axis(roll, float3::z_axis()) * from_angle_axis(pitch, float3::x_axis()) * from_angle_axis(yaw, float3::y_axis());
    }

    inline quat conj() {
        return vec * float4(float3(-1), 1);
    }

    inline float norm() {
        return vec.len();
    }

    inline quat operator+(quat rhs) {
        return vec + rhs.vec;
    }

    inline quat operator-(quat rhs) {
        return vec - rhs.vec;
    }

    inline quat operator*(quat rhs) {
        return quat(vec.xyz().cross(rhs.vec.xyz()) + vec.www()*rhs.vec.xyz() + vec.xyz()*rhs.vec.www(),
            conj().vec.dot(rhs.vec));
    }

    inline quat& operator+=(quat rhs) {
        (*this) = *this + rhs;
        return *this;
    }

    inline quat& operator-=(quat rhs) {
        (*this) = (*this) - rhs;
        return *this;
    }

    inline quat& operator*=(quat rhs) {
        (*this) = (*this) * rhs;
        return *this;
    }

    inline float4 operator==(quat rhs) {
        return (vec == rhs.vec);
    }

    inline float4 operator!=(quat rhs) {
        return (vec != rhs.vec);
    }

    inline float4 operator<(quat rhs) {
        return (vec < rhs.vec);
    }

    inline float4 operator<=(quat rhs) {
        return (vec <= rhs.vec);
    }

    inline float4 operator>=(quat rhs) {
        return (vec >= rhs.vec);
    }

    inline float4 operator>(quat rhs) {
        return (vec > rhs.vec);
    }

    inline quat inverse() {
        return conj().vec/vec.len2();
    }

    inline float4 rotate(float4 vec) {
        return ((*this) * quat(vec) * conj()).vec;
    }

    inline float3 rotate(float3 vec) {
        return rotate(float4(vec, 1)).xyz();
    }

    inline quat normalized() {
        return vec.normalized();
    }

    inline float4x4 rot_mat4_form() {
        float4x4 lq(vec.wzyx() * float4(1, 1, -1, -1), vec.zwxy() * float4(-1, 1, 1, -1), 
            vec.yxwz() * float4(1, -1, 1, -1), vec);
        
        float4x4 rqs(vec.wzyx() * float4(1, 1, -1, 1), vec.zwxy() * float4(-1, 1, 1, 1), 
            vec.yxwz() * float4(1, -1, 1, 1), vec * float4(-1, -1, -1, 1));
        
        return lq * rqs * (1/norm());
    }

    inline float3x3 rot_mat3_form() {
        return float3x3(rot_mat4_form());
    }

    inline quat exponent(float t) {
        float angle = acosf(vec.w());
        return quat(sinf(t * angle)*vec.xyz().normalized(), cosf(t * angle));
    }
    inline quat operator/(float rhs) {
        return vec * 1/rhs;
    }

    float4 vec;
};

static inline quat operator*(quat lhs, float rhs) {
    return lhs.vec * rhs;
}

static inline quat operator*(float lhs, quat rhs) {
    return rhs * lhs;
}

}

