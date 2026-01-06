#pragma once



#include "fonge/constants.hpp"
#include "fonge/matrix_float.hpp"
#include "matrix_float.hpp"
#include "quaternion_float.hpp"
#include "shapes.hpp"
#include "vector_float.hpp"
#include <cmath>
#include <complex.h>

namespace fonge {
    inline float3x3 translation3f(float2 displacement) {
        return float3x3::identity() + float3x3(0, 0, float3(displacement, 0));
    }

    inline float4x4 translation4f(float3 displacement) {
        return float4x4::identity() + float4x4(0, 0, 0, float4(displacement, 0));
    }

    inline float2x2 rotation2f(float theta) {
        return float2x2(cosf(theta), -sinf(theta), sinf(theta), cosf(theta));
    }

    inline float3x3 rotation3f(quat q) {
        return q.rot_mat3_form(); 
    }

    inline float4x4 rotation4f(quat q) {
        return q.rot_mat4_form();
    }

    inline float2x2 scale2f(float2 scale) {
        return float2x2(scale.x() * float2::x_axis(), scale.y() * float2::y_axis());
    }

    inline float3x3 scale3f(float3 scale) {
        return float3x3(scale.x() * float3::x_axis(), scale.y() * float3::y_axis(), scale.z() * float3::z_axis());
    }

    inline float4x4 scale4f(float4 scale) {
        return float4x4(scale.x() * float4::x_axis(), scale.y() * float4::y_axis(), 
            scale.z() * float4::z_axis(), scale.w() * float4::w_axis());
    }

    // Reverse-Z perspective projection matrix. If far is 0, interpret as infinite far plane.
    inline float4x4 perspectivef(float h_fov, float aspect, float near, float far = 0) {
        h_fov *= DEG2RAD;
        float sx = near * tanh(h_fov/2);
        float sy = sx/aspect;

        if (far == 0.f) {
            return float4x4(sx * float4::x_axis(), sy * float4::y_axis(), 
                -float4::w_axis(), near * float4::z_axis());
        } else {
            return float4x4(sx * float4::x_axis(), sy * float4::y_axis(), 
                float4(0, 0, near/(far - near), -1), far * near * float4::z_axis()/(far - near));
        }
    }

    inline float4x4 orthographicf(AABB3f frustum_box) {
        
    }
}

