#pragma once

#include <math.h>

namespace fonge {
// Multiply by to convert from degrees to radians.
constexpr double DEG2RAD = M_PI / 180;

// Multiply by to convert from radians to degrees.
constexpr double RAD2DEG = 180 / M_PI;

// e
constexpr double E = M_E;

// pi
constexpr double PI = M_PI;

// The golden ratio.
constexpr double PHI = 1.6180339887498948482045868343656381177203;
} // namespace fonge
