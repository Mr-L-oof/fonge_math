#include "vector_float.hpp"

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
        return vec.len2();
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

    inline float4 rotate(float4 vec) {
        return ((*this) * quat(vec) * conj()).vec;
    }

    inline float3 rotate(float3 vec) {
        return rotate(float4(vec, 1)).xyz();
    }

    inline quat normalized() {
        return vec.normalized();
    }

    float4 vec;
};

static inline quat operator*(quat lhs, float rhs) {
    return lhs.vec * rhs;
}

static inline quat operator*(float lhs, quat rhs) {
    return rhs * lhs;
}

static inline quat operator/(quat lhs, float rhs) {
    return lhs * 1/rhs;
}

}

