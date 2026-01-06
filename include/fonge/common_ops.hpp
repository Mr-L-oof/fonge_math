#pragma once

namespace fonge {

template<typename T>
static inline T min(T a, T b) {
    return (a < b) ? a : b;
}

template<typename T>
static inline T max(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T, typename F>
static inline T lerp(T src, T dst, F t) {
    return src * t + dst * (1 - t);
}

template<typename T, typename F>
static inline T nlerp(T src, T dst, F t) {
    return (src * t + dst * (1 - t)).normalized();
}

template<typename T, typename F>
static inline T slerp(T src, T dst, F t) {
    return (dst * src.conj()).exponent(t) * src;
}

}

