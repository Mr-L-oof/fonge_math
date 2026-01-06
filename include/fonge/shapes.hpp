#pragma once

#include "common_ops.hpp"
#include "fonge/vector_double.hpp"
#include "vector_float.hpp"

namespace fonge {

template<typename T>
struct AABB {
    inline AABB(T min, T max) 
    : min_point(min), max_point(max) {}

    inline AABB<T> from_dims(T center, T dimensions) {
        return AABB<T>(center - dimensions/2, center + dimensions/2);
    }

    inline AABB<T> collide(AABB<T> other) {
        return AABB2f(max(min_point, other.min_point), min(max_point, other.max_point));
    }

    inline AABB<T> merge(AABB<T> other) {
        return AABB2f(min(min_point, other.min_point), max(max_point, other.max_point));
    }

    inline T dimensions() {
        return max_point - min_point;
    }

    inline T centroid() {
        return (min_point + max_point)/2;
    }

    T min_point, max_point;
};

typedef AABB<float2> AABB2f;
typedef AABB<float3> AABB3f;
typedef AABB<double2> AABB2d;
typedef AABB<double3> AABB3d;

}
