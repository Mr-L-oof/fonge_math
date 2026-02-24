#pragma once

#include <simde/x86/avx512.h>

namespace fonge {

#define permute_pd_custom(simdvar, ids)                                        \
  simde_mm256_shuffle_pd((simdvar), (simdvar), (ids))

typedef double double1;
struct double2;
struct double3;
struct double4;

struct double2 {
  inline double2() : simd(simde_mm256_setzero_pd()) {}

  inline double2(double all) : simd(simde_mm256_set1_pd(all)) {}

  inline double2(simde__m256d vec) : simd(vec) {}

  inline double2(double x, double y) { simd = simde_mm256_setr_pd(x, y, 0, 0); }

  inline double2 operator+(double2 rhs) {
    return simde_mm256_add_pd(simd, rhs.simd);
  }

  inline double2 operator-(double2 rhs) {
    return simde_mm256_sub_pd(simd, rhs.simd);
  }

  inline double2 operator*(double2 rhs) {
    return simde_mm256_mul_pd(simd, rhs.simd);
  }

  inline double2 operator/(double2 rhs) {
    return simde_mm256_div_pd(simd, rhs.simd);
  }

  inline double2 &operator+=(double2 rhs) {
    (*this) = (*this) + rhs;
    return *this;
  }

  inline double2 &operator-=(double2 rhs) {
    (*this) = (*this) - rhs;
    return *this;
  }

  inline double2 &operator*=(double2 rhs) {
    (*this) = (*this) * rhs;
    return *this;
  }

  inline double2 &operator/=(double2 rhs) {
    (*this) = (*this) / rhs;
    return *this;
  }

  inline bool operator==(double2 rhs) {
    return double2(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_EQ))
        .all();
  }

  inline bool operator!=(double2 rhs) {
    return double2(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_NE))
        .all();
  }

  inline bool operator<(double2 rhs) {
    return double2(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_LT))
        .all();
  }

  inline bool operator<=(double2 rhs) {
    return double2(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_LE))
        .all();
  }

  inline bool operator>=(double2 rhs) {
    return double2(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_NLT))
        .all();
  }

  inline bool operator>(double2 rhs) {
    return double2(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_NLE))
        .all();
  }

  inline double2 operator-() { return simde_x_mm256_negate_pd(simd); }

  inline double2 abs() { return simde_x_mm256_abs_pd(simd); }

  inline uint32_t mask() { return simde_mm256_movemask_pd(simd) & 0b11; }

  inline bool any() { return mask() != 0; }

  inline bool all() { return mask() == 0b11; }

  inline double operator[](size_t i) {
    double out[4];
    simde_mm256_store_pd(out, simd);
    return out[i];
  }

  inline double dot(double2 rhs) {
    double2 out = (*this) * rhs;
    out = simde_mm256_hadd_pd(out.simd, out.simd);
    return simde_mm256_cvtsd_f64(out.simd);
  }

  double2 cross() { return yx() * double2(1, -1); }

#include "swizzles/double2_swizzles_decl"

  inline double len2() { return dot(*this); }

  inline double len() { return sqrtf(len2()); }

  inline double2 normalized() { return (*this) / len(); }

  static inline double2 one() { return double2(1); }

  static inline double2 up() { return double2(0, 1); }

  static inline double2 down() { return double2(0, -1); }

  static inline double2 left() { return double2(-1, 0); }

  static inline double2 right() { return double2(1, 0); }

  static inline double2 x_axis() { return double2(1, 0); }

  static inline double2 y_axis() { return double2(0, 1); }

  simde__m256d simd;
};

static inline double2 operator*(double2 lhs, double rhs) {
  return lhs * double2(rhs);
}

static inline double2 operator*(double lhs, double2 rhs) {
  return double2(lhs) * rhs;
}

static inline double2 operator/(double2 lhs, double rhs) {
  return lhs / double2(rhs);
}

struct double3 {
  inline double3(double all) : simd(simde_mm256_set1_pd(all)) {}

  inline double3(simde__m256d vec) : simd(vec) {}

  inline double3() : simd(simde_mm256_setzero_pd()) {}

  inline double3 operator+(double3 rhs) {
    return simde_mm256_add_pd(simd, rhs.simd);
  }

  inline double3 operator-(double3 rhs) {
    return simde_mm256_sub_pd(simd, rhs.simd);
  }

  inline double3 operator*(double3 rhs) {
    return simde_mm256_mul_pd(simd, rhs.simd);
  }

  inline double3 operator/(double3 rhs) {
    return simde_mm256_div_pd(simd, rhs.simd);
  }

  inline double3 &operator+=(double3 rhs) {
    (*this) = (*this) + rhs;
    return *this;
  }

  inline double3 &operator-=(double3 rhs) {
    (*this) = (*this) - rhs;
    return *this;
  }

  inline double3 &operator*=(double3 rhs) {
    (*this) = (*this) * rhs;
    return *this;
  }

  inline double3 &operator/=(double3 rhs) {
    (*this) = (*this) / rhs;
    return *this;
  }

  inline bool operator==(double3 rhs) {
    return double3(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_EQ))
        .all();
  }

  inline bool operator!=(double3 rhs) {
    return double3(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_NE))
        .all();
  }

  inline bool operator<(double3 rhs) {
    return double3(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_LT))
        .all();
  }

  inline bool operator<=(double3 rhs) {
    return double3(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_LE))
        .all();
  }

  inline bool operator>=(double3 rhs) {
    return double3(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_NLT))
        .all();
  }

  inline bool operator>(double3 rhs) {
    return double3(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_NLE))
        .all();
  }

  inline double3 operator-() { return simde_x_mm256_negate_pd(simd); }

  inline double3 abs() { return simde_x_mm256_abs_pd(simd); }

  inline uint32_t mask() { return simde_mm256_movemask_pd(simd) & 0b111; }

  inline bool any() { return mask() != 0; }

  inline bool all() { return mask() == 0b111; }

  inline double operator[](size_t i) {
    double out[4];
    simde_mm256_store_pd(out, simd);
    return out[i];
  }

  inline double dot(double3 rhs) {
    double3 out = (*this) * rhs;
    return (out.xxx() + out.yyy() + out.zzz()).x();
  }

  inline double3(double x, double y, double z) {
    simd = simde_mm256_setr_pd(x, y, z, 0);
  }

  inline double3(double2 xy, double z = 0.f) {
    simd = simde_mm256_shuffle_pd(xy.simd, double2(z).simd,
                                  SIMDE_MM_SHUFFLE(1, 0, 1, 0));
  }

  inline double3(double x, double2 yz) { (*this) = double3(yz, x).zxy(); }

  inline double3 cross(double3 rhs) {
    return (zxy() * rhs - (*this) * rhs.zxy()).zxy();
  }

#include "swizzles/double3_swizzles_decl"

  inline double len2() { return dot(*this); }

  inline double len() { return sqrtf(len2()); }

  inline double3 normalized() { return (*this) / len(); }

  static inline double3 one() { return double3(1); }

  static inline double3 x_axis() { return double3(1, 0, 0); }

  static inline double3 y_axis() { return double3(0, 1, 0); }

  static inline double3 z_axis() { return double3(0, 0, 1); }

  static inline double3 right() { return x_axis(); }

  static inline double3 left() { return -x_axis(); }

  static inline double3 up() { return y_axis(); }

  static inline double3 down() { return -y_axis(); }

  static inline double3 forward() { return -z_axis(); }

  static inline double3 backward() { return z_axis(); }

  simde__m256d simd;
};

static inline double3 operator*(double3 lhs, double rhs) {
  return lhs * double3(rhs);
}

static inline double3 operator*(double lhs, double3 rhs) {
  return double3(lhs) * rhs;
}

static inline double3 operator/(double3 lhs, double rhs) {
  return lhs / double3(rhs);
}

struct double4 {
  inline double4(const double4 &other) : simd(other.simd) {}

  inline double4(double all) : simd(simde_mm256_set1_pd(all)) {}

  inline double4(simde__m256d vec) : simd(vec) {}

  inline double4(double x, double y, double z, double w) {
    simd = simde_mm256_setr_pd(x, y, z, w);
  }

  inline double4() : simd(simde_mm256_setzero_pd()) {}

  inline double4(double3 xyz, double w = 0) {
    simd = simde_mm256_blend_pd(xyz.simd, simde_mm256_set1_pd(w), 0b1000);
  }

  inline double4(double x, double3 yzw) { (*this) = double4(yzw, x).wxyz(); }

  inline double4(double2 xy, double2 zw = double2()) {
    simd = simde_mm256_blend_pd(xy.simd, zw.simd, 0b1100);
  }

  inline double4(double2 xy, double z, double w) {
    (*this) = double4(xy, double2(z, w));
  }

  inline double4(double x, double2 yz, double w) {
    (*this) = double4(yz, x, w).zxyw();
  }

  inline double4(double x, double y, double2 zw) {
    (*this) = double4(double2(x, y), zw);
  }

  inline double4 operator+(double4 rhs) {
    return simde_mm256_add_pd(simd, rhs.simd);
  }

  inline double4 operator-(double4 rhs) {
    return simde_mm256_sub_pd(simd, rhs.simd);
  }

  inline double4 operator*(double4 rhs) {
    return simde_mm256_mul_pd(simd, rhs.simd);
  }

  inline double4 operator/(double4 rhs) {
    return simde_mm256_div_pd(simd, rhs.simd);
  }

  inline double4 &operator+=(double4 rhs) {
    (*this) = (*this) + rhs;
    return *this;
  }

  inline double4 &operator-=(double4 rhs) {
    (*this) = (*this) - rhs;
    return *this;
  }

  inline double4 &operator*=(double4 rhs) {
    (*this) = (*this) * rhs;
    return *this;
  }

  inline double4 &operator/=(double4 rhs) {
    (*this) = (*this) / rhs;
    return *this;
  }

  inline bool operator==(double4 rhs) {
    return double4(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_EQ))
        .all();
  }

  inline bool operator!=(double4 rhs) {
    return double4(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_NE))
        .all();
  }

  inline bool operator<(double4 rhs) {
    return double4(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_LT))
        .all();
  }

  inline bool operator<=(double4 rhs) {
    return double4(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_LE))
        .all();
  }

  inline bool operator>=(double4 rhs) {
    return double4(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_NLT))
        .all();
  }

  inline bool operator>(double4 rhs) {
    return double4(simde_mm256_cmp_pd(simd, rhs.simd, SIMDE_MM_CMPINT_NLE))
        .all();
  }

  inline double4 operator-() { return simde_x_mm256_negate_pd(simd); }

  inline double4 abs() { return simde_x_mm256_abs_pd(simd); }

  inline uint32_t mask() { return simde_mm256_movemask_pd(simd) & 0b1111; }

  inline bool any() { return mask() != 0; }

  inline bool all() { return mask() == 0b1111; }

  inline double operator[](size_t i) {
    double out[4];
    simde_mm256_store_pd(out, simd);
    return out[i];
  }

  inline double dot(double4 rhs) {
    double4 out = (*this) * rhs;
    return (out.xxxx() + out.yyyy() + out.zzzz() + out.wwww()).x();
  }

  inline double4 cross(double4 mhs, double4 rhs) {
    return (yxxx() * (mhs.zzyy() * rhs.wwwz() - rhs.zzyy() * mhs.wwwz()) -
            zzyy() * (mhs.yxxx() * rhs.wwwz() - rhs.yxxx() * mhs.wwwz()) +
            wwwz() * (mhs.yxxx() * rhs.zzyy() - rhs.yxxx() * mhs.zzyy())) *
           double4(1, -1, 1, -1);
  }

#include "swizzles/double4_swizzles_decl"

  inline double len2() { return dot(*this); }

  inline double len() { return sqrtf(len2()); }

  inline double4 normalized() { return (*this) / len(); }

  static inline double4 one() { return double4(1); }

  static inline double4 x_axis() { return double4(1, 0, 0, 0); }

  static inline double4 y_axis() { return double4(0, 1, 0, 0); }

  static inline double4 z_axis() { return double4(0, 0, 1, 0); }

  static inline double4 w_axis() { return double4(0, 0, 0, 1); }

  static inline double4 right() { return x_axis(); }

  static inline double4 left() { return -x_axis(); }

  static inline double4 up() { return y_axis(); }

  static inline double4 down() { return -y_axis(); }

  static inline double4 forward() { return -z_axis(); }

  static inline double4 backward() { return z_axis(); }

  simde__m256d simd;
};

static inline double4 operator*(double4 lhs, double rhs) {
  return lhs * double4(rhs);
}

static inline double4 operator*(double lhs, double4 rhs) {
  return double4(lhs) * rhs;
}

static inline double4 operator/(double4 lhs, double rhs) {
  return lhs / double4(rhs);
}

#include "swizzles/double2_swizzles_impl"
#include "swizzles/double3_swizzles_impl"
#include "swizzles/double4_swizzles_impl"

} // namespace fonge
