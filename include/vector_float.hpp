#pragma once

#include <simde/x86/avx512.h>

namespace fonge {

#define permute_ps_custom(simdvar, ids) simde_mm_shuffle_ps((simdvar), (simdvar), (ids))

typedef float float1;
struct float2;
struct float3;
struct float4;

struct float2 {
    inline float2(float all)
    : simd(simde_mm_set1_ps(all)) {}

    inline float2(simde__m128 vec)
    : simd(vec) {}

    inline float2(float x, float y) {
        simd = simde_mm_setr_ps(x, y, 0, 0);
    }

    inline float2()
    : simd(simde_mm_setzero_ps()) {}

    inline float2 operator+(float2 rhs) {
        return simde_mm_add_ps(simd, rhs.simd);
    }

    inline float2 operator-(float2 rhs) {
        return simde_mm_sub_ps(simd, rhs.simd);
    }

    inline float2 operator*(float2 rhs) {
        return simde_mm_mul_ps(simd, rhs.simd);
    }

    inline float2 operator/(float2 rhs) {
        return simde_mm_div_ps(simd, rhs.simd);
    }

    inline float2& operator+=(float2 rhs) {
        (*this) = (*this) + rhs;
        return *this;
    } 

    inline float2& operator-=(float2 rhs) {
        (*this) = (*this) - rhs;
        return *this;
    }

    inline float2& operator*=(float2 rhs) {
        (*this) = (*this) * rhs;
        return *this;
    }

    inline float2& operator/=(float2 rhs) {
        (*this) = (*this)/rhs;
        return *this;
    }

    inline float2 operator==(float2 rhs) {
        return simde_mm_cmpeq_ps(simd, rhs.simd);
    }

    inline float2 operator!=(float2 rhs) {
        return simde_mm_cmpneq_ps(simd, rhs.simd);
    }

    inline float2 operator<(float2 rhs) {
        return simde_mm_cmplt_ps(simd, rhs.simd);
    }

    inline float2 operator<=(float2 rhs) {
        return simde_mm_cmple_ps(simd, rhs.simd);
    }

    inline float2 operator>=(float2 rhs) {
        return simde_mm_cmpge_ps(simd, rhs.simd);
    }

    inline float2 operator>(float2 rhs) {
        return simde_mm_cmpgt_ps(simd, rhs.simd);
    }

    inline uint32_t mask() {
        return simde_mm_movemask_ps(simd) & 0b11;
    }

    inline float2 operator-() {
        return simde_x_mm_negate_ps(simd);
    }

    inline float2 abs() {
        return simde_x_mm_abs_ps(simd);
    }

    inline bool any() {
        return mask() != 0;
    }

    inline bool all() {
        return mask() == 0b11;
    }

    inline float operator[](size_t i) {
        float out[4];
        simde_mm_store_ps(out, simd);
        return out[i];
    }

    inline float dot(float2 rhs) {
        return simde_mm_cvtss_f32(simde_mm_dp_ps(simd, rhs.simd, 0b00111111));
    }

    float2 cross() {
        return yx() * float2(1, -1);
    }

    #include "swizzles/float2_swizzles_decl"

    inline float len2() {
        return dot(*this);
    }

    inline float len() {
        return sqrtf(len2());
    }

    inline float2 normalized() {
        return (*this)/len();
    }

    static inline float2 one() {
        return float2(1);
    }

    static inline float2 up() {
        return float2(0, 1);
    }

    static inline float2 down() {
        return float2(0, -1);
    }

    static inline float2 left() {
        return float2(-1, 0);
    }

    static inline float2 right() {
        return float2(1, 0);
    }

    static inline float2 x_axis() {
        return float2(1, 0);
    }

    static inline float2 y_axis() {
        return float2(0, 1);
    }

    simde__m128 simd;
};

static inline float2 operator*(float2 lhs, float rhs) {
    return lhs * float2(rhs);
}

static inline float2 operator*(float lhs, float2 rhs) {
    return float2(lhs) * rhs;
}

static inline float2 operator/(float2 lhs, float rhs) {
    return lhs/float2(rhs);
}

struct float3 {
    inline float3(float all)
    : simd(simde_mm_set1_ps(all)) {}

    inline float3(simde__m128 vec)
    : simd(vec) {}

    inline float3 operator+(float3 rhs) {
        return simde_mm_add_ps(simd, rhs.simd);
    }

    inline float3 operator-(float3 rhs) {
        return simde_mm_sub_ps(simd, rhs.simd);
    }

    inline float3 operator*(float3 rhs) {
        return simde_mm_mul_ps(simd, rhs.simd);
    }

    inline float3 operator/(float3 rhs) {
        return simde_mm_div_ps(simd, rhs.simd);
    }

    inline float3& operator+=(float3 rhs) {
        (*this) = (*this) + rhs;
        return *this;
    } 

    inline float3& operator-=(float3 rhs) {
        (*this) = (*this) - rhs;
        return *this;
    }

    inline float3& operator*=(float3 rhs) {
        (*this) = (*this) * rhs;
        return *this;
    }

    inline float3& operator/=(float3 rhs) {
        (*this) = (*this)/rhs;
        return *this;
    }

    inline float3 operator==(float3 rhs) {
        return simde_mm_cmpeq_ps(simd, rhs.simd);
    }

    inline float3 operator!=(float3 rhs) {
        return simde_mm_cmpneq_ps(simd, rhs.simd);
    }

    inline float3 operator<(float3 rhs) {
        return simde_mm_cmplt_ps(simd, rhs.simd);
    }

    inline float3 operator<=(float3 rhs) {
        return simde_mm_cmple_ps(simd, rhs.simd);
    }

    inline float3 operator>=(float3 rhs) {
        return simde_mm_cmpge_ps(simd, rhs.simd);
    }

    inline float3 operator>(float3 rhs) {
        return simde_mm_cmpgt_ps(simd, rhs.simd);
    }

    inline uint32_t mask() {
        return simde_mm_movemask_ps(simd) & 7;
    }

    inline float3 operator-() {
        return simde_x_mm_negate_ps(simd);
    }

    inline float3 abs() {
        return simde_x_mm_abs_ps(simd);
    }

    inline bool any() {
        return mask() != 0;
    }

    inline bool all() {
        return mask() == 0b111;
    }

    inline float operator[](size_t i) {
        float out[4];
        simde_mm_store_ps(out, simd);
        return out[i];
    }

    inline float dot(float3 rhs) {
        return simde_mm_cvtss_f32(simde_mm_dp_ps(simd, rhs.simd, 0b01111111));
    }

    inline float3(float x, float y, float z) {
        simd = simde_mm_setr_ps(x, y, z, 0);
    }

    inline float3()
    : simd(simde_mm_setzero_ps()) {}

    inline float3(float2 xy, float z = 0.f) {
        simd = simde_mm_movelh_ps(xy.simd, simde_mm_set1_ps(z));
    }

    inline float3(float x, float2 yz) {
        simd = permute_ps_custom(simde_mm_movelh_ps(yz.simd, simde_mm_set1_ps(x)), SIMDE_MM_SHUFFLE(3, 1, 0, 2)); 
    }

    inline float3 cross(float3 rhs) {
        return (zxy()*rhs - (*this)*rhs.zxy()).zxy();
    }

    #include "swizzles/float3_swizzles_decl"

    inline float len2() {
        return dot(*this);
    }

    inline float len() {
        return sqrtf(len2());
    }

    inline float3 normalized() {
        return (*this)/len();
    }

    static inline float3 one() {
        return float3(1);
    }

    static inline float3 x_axis() {
        return float3(1, 0, 0);
    }

    static inline float3 y_axis() {
        return float3(0, 1, 0);
    }

    static inline float3 z_axis() {
        return float3(0, 0, 1);
    }

    static inline float3 right() {
        return x_axis();
    }

    static inline float3 left() {
        return -x_axis();
    }

    static inline float3 up() {
        return y_axis();
    }

    static inline float3 down() {
        return -y_axis();
    }

    static inline float3 forward() {
        return -z_axis();
    }

    static inline float3 backward() {
        return z_axis();
    }

    simde__m128 simd;
};

static inline float3 operator*(float3 lhs, float rhs) {
    return lhs * float3(rhs);
}

static inline float3 operator*(float lhs, float3 rhs) {
    return float3(lhs) * rhs;
}

static inline float3 operator/(float3 lhs, float rhs) {
    return lhs/float3(rhs);
}

struct float4 {
    inline float4(const float4& other)
    : simd(other.simd) {}

    inline float4(float all)
    : simd(simde_mm_set1_ps(all)) {}

    inline float4(simde__m128 vec)
    : simd(vec) {}

    inline float4(float x, float y, float z, float w) {
        simd = simde_mm_setr_ps(x, y, z, w);
    }

    inline float4()
    : simd(simde_mm_setzero_ps()) {}

    inline float4(float3 xyz, float w = 0) {
        simd = simde_mm_move_ss(
            permute_ps_custom(xyz.simd, SIMDE_MM_SHUFFLE(2, 1, 0, 3)), simde_mm_set1_ps(w));
        simd = permute_ps_custom(simd, SIMDE_MM_SHUFFLE(0, 3, 2, 1));
    }

    inline float4(float x, float3 yzw) {
        (*this) = float4(yzw, x).wxyz();
    }

    inline float4(float2 xy, float2 zw = float2()) {
        simd = simde_mm_movelh_ps(xy.simd, zw.simd);
    }

    inline float4(float2 xy, float z, float w) {
        (*this) = float4(xy, float2(z, w));
    }

    inline float4(float x, float2 yz, float w) {
        (*this) = float4(yz, x, w).zxyw();
    }

    inline float4(float x, float y, float2 zw) {
        (*this) = float4(float2(x, y), zw);
    }


    inline float4 operator+(float4 rhs) {
        return simde_mm_add_ps(simd, rhs.simd);
    }

    inline float4 operator-(float4 rhs) {
        return simde_mm_sub_ps(simd, rhs.simd);
    }

    inline float4 operator*(float4 rhs) {
        return simde_mm_mul_ps(simd, rhs.simd);
    }

    inline float4 operator/(float4 rhs) {
        return simde_mm_div_ps(simd, rhs.simd);
    }

    inline float4& operator+=(float4 rhs) {
        (*this) = (*this) + rhs;
        return *this;
    } 

    inline float4& operator-=(float4 rhs) {
        (*this) = (*this) - rhs;
        return *this;
    }

    inline float4& operator*=(float4 rhs) {
        (*this) = (*this) * rhs;
        return *this;
    }

    inline float4& operator/=(float4 rhs) {
        (*this) = (*this)/rhs;
        return *this;
    }

    inline float4 operator==(float4 rhs) {
        return simde_mm_cmpeq_ps(simd, rhs.simd);
    }

    inline float4 operator!=(float4 rhs) {
        return simde_mm_cmpneq_ps(simd, rhs.simd);
    }

    inline float4 operator<(float4 rhs) {
        return simde_mm_cmplt_ps(simd, rhs.simd);
    }

    inline float4 operator<=(float4 rhs) {
        return simde_mm_cmple_ps(simd, rhs.simd);
    }

    inline float4 operator>=(float4 rhs) {
        return simde_mm_cmpge_ps(simd, rhs.simd);
    }

    inline float4 operator>(float4 rhs) {
        return simde_mm_cmpgt_ps(simd, rhs.simd);
    }

    inline uint32_t mask() {
        return simde_mm_movemask_ps(simd) & 0b1111;
    }

    inline float4 operator-() {
        return simde_x_mm_negate_ps(simd);
    }

    inline float4 abs() {
        return simde_x_mm_abs_ps(simd);
    }

    inline bool any() {
        return mask() != 0;
    }

    inline bool all() {
        return mask() >= 0b1111;
    }

    inline float operator[](size_t i) {
        float out[4];
        simde_mm_store_ps(out, simd);
        return out[i];
    }

    inline float dot(float4 rhs) {
        return simde_mm_cvtss_f32(simde_mm_dp_ps(simd, rhs.simd, 0b11111111));
    }

    inline float4 cross(float4 mhs, float4 rhs) {
        return float4(
            yzw().dot(mhs.yzw().cross(rhs.yzw())),
            -xzw().dot(mhs.xzw().cross(rhs.xzw())),
            xyw().dot(mhs.xyw().cross(rhs.xyw())),
            -xyz().dot(mhs.xyz().cross(rhs.xyz()))
        );
    }

    #include "swizzles/float4_swizzles_decl"

    inline float len2() {
        return dot(*this);
    }

    inline float len() {
        return sqrtf(len2());
    }

    inline float4 normalized() {
        return (*this)/len();
    }

    static inline float4 one() {
        return float4(1);
    }

    static inline float4 x_axis() {
        return float4(1, 0, 0, 0);
    }

    static inline float4 y_axis() {
        return float4(0, 1, 0, 0);
    }

    static inline float4 z_axis() {
        return float4(0, 0, 1, 0);
    }

    static inline float4 w_axis() {
        return float4(0, 0, 0, 1);
    }

    static inline float4 right() {
        return x_axis();
    }

    static inline float4 left() {
        return -x_axis();
    }

    static inline float4 up() {
        return y_axis();
    }

    static inline float4 down() {
        return -y_axis();
    }

    static inline float4 forward() {
        return -z_axis();
    }

    static inline float4 backward() {
        return z_axis();
    }
    
    simde__m128 simd;
};

static inline float4 operator*(float4 lhs, float rhs) {
    return lhs * float4(rhs);
}

static inline float4 operator*(float lhs, float4 rhs) {
    return float4(lhs) * rhs;
}

static inline float4 operator/(float4 lhs, float rhs) {
    return lhs/float4(rhs);
}

#include "swizzles/float2_swizzles_impl"
#include "swizzles/float3_swizzles_impl"
#include "swizzles/float4_swizzles_impl"

}
