#include "vector_double.hpp"

namespace fonge {

struct dquat {
    inline dquat(double4 a)
    : vec(a) {}

    inline dquat()
    : vec(0, 0, 0, 1) {}

    inline dquat(double3 complex_part, double real_part) 
    : vec(complex_part, real_part) {}

    static inline dquat from_angle_axis(double angle, double3 axis) {
        return double4(axis * sinf(angle/2), cosf(angle/2));
    }

    static inline dquat from_cosangle_axis(double cosangle, double3 axis) {
        return double4(axis * sqrt(1-cosangle*cosangle),cosangle);
    }

    static inline dquat from_euler_zxy(double pitch, double yaw, double roll) {
        return from_angle_axis(roll, double3::z_axis()) * from_angle_axis(pitch, double3::x_axis()) * from_angle_axis(yaw, double3::y_axis());
    }

    inline dquat conj() {
        return vec * double4(double3(-1), 1);
    }

    inline double norm() {
        return vec.len2();
    }

    inline dquat operator+(dquat rhs) {
        return vec + rhs.vec;
    }

    inline dquat operator-(dquat rhs) {
        return vec - rhs.vec;
    }

    inline dquat operator*(dquat rhs) {
        return dquat(vec.xyz().cross(rhs.vec.xyz()) + vec.www()*rhs.vec.xyz() + vec.xyz()*rhs.vec.www(),
            conj().vec.dot(rhs.vec));
    }

    inline dquat& operator+=(dquat rhs) {
        (*this) = *this + rhs;
        return *this;
    }

    inline dquat& operator-=(dquat rhs) {
        (*this) = (*this) - rhs;
        return *this;
    }

    inline dquat& operator*=(dquat rhs) {
        (*this) = (*this) * rhs;
        return *this;
    }

    inline double4 operator==(dquat rhs) {
        return (vec == rhs.vec);
    }

    inline double4 operator!=(dquat rhs) {
        return (vec != rhs.vec);
    }

    inline double4 operator<(dquat rhs) {
        return (vec < rhs.vec);
    }

    inline double4 operator<=(dquat rhs) {
        return (vec <= rhs.vec);
    }

    inline double4 operator>=(dquat rhs) {
        return (vec >= rhs.vec);
    }

    inline double4 operator>(dquat rhs) {
        return (vec > rhs.vec);
    }

    inline double4 rotate(double4 vec) {
        return ((*this) * dquat(vec) * conj()).vec;
    }

    inline double3 rotate(double3 vec) {
        return rotate(double4(vec, 1)).xyz();
    }

    inline dquat normalized() {
        return vec.normalized();
    }

    double4 vec;
};

static inline dquat operator*(dquat lhs, double rhs) {
    return lhs.vec * rhs;
}

static inline dquat operator*(double lhs, dquat rhs) {
    return rhs * lhs;
}

static inline dquat operator/(dquat lhs, double rhs) {
    return lhs * 1/rhs;
}

}

