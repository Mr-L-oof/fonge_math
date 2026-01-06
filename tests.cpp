#include <fonge/vector_float.hpp>
#include <fonge/vector_double.hpp>
#include <fonge/quaternion_float.hpp>
#include <fonge/quaternion_double.hpp>
#include <fonge/constants.hpp>
#include <fonge/matrix_double.hpp>

#include <assert.h>

using namespace fonge;

int main(int argc, char *argv[]) {
    if (argc > 1) {
        switch (atoi(argv[1])) {
            case 0: {
                // +, -, *, /, dot(), cross() for float2
                fonge::float2 a(6, 7), b(7, 10);

                // basic validation
                assert((a + b == fonge::float2(13, 17)) );
                assert((b - a == fonge::float2(1, 3)) );
                assert((a * b == fonge::float2(42, 70)) );
                assert((a/b == fonge::float2(6./7., 0.7)) );
                assert(a.dot(b) == 42 + 70);
                assert((a.cross() == fonge::float2(7, -6)) );
                assert((b.cross() == fonge::float2(10, -7)) );

                // properties
                assert((a + b == b + a) );
                assert((a - b == -b + a) );
                assert((a - b == -(b - a)) );
                assert((a * b == b * a) );
                assert((a * fonge::float2::one() == a) );
                assert((a * fonge::float2() == fonge::float2()) );
                assert((a/b == fonge::float2::one()/(b/a)) );
                assert((a/a == fonge::float2::one()) );
                assert((a/fonge::float2::one() == a) );
                assert(a.dot(b) == b.dot(a));
                assert(a.dot(a) == a.len2());
                assert(a.dot(b) == a.x()*b.x() + a.y()*b.y());
                assert(a.dot(fonge::float2::x_axis()) == a.x());
                assert(a.dot(fonge::float2()) == 0);
                assert(a.cross().dot(a) == 0);
                assert(a.dot(b.cross()) == -b.dot(a.cross()));
                break;
            }

            case 1: {
                // +, -, *, /, dot(), cross() for float3
                float3 a(6, 7, 8), b(1, 10, 3), c(21, 6, 3);
                // basic validation
                assert((a + b == float3(7, 17, 11)) );
                assert((a - b == float3(5, -3, 5)) );
                assert((a * b == float3(6, 70, 24)) );
                assert((a/b == float3(6, 0.7, 8./3.)) );
                assert(a.dot(b) == 6 + 70 + 24);
                assert((a.cross(b) == float3(21-80,8-18,60-7)) );
                // properties
                assert((a + b == b + a) );
                assert((a - b == -b + a) );
                assert((a - b == -(b - a)) );
                assert((a * b == b * a) );
                assert((a * fonge::float3::one() == a) );
                assert((a * fonge::float3() == fonge::float3()) );
                assert((a/b == fonge::float3::one()/(b/a)) );
                assert((a/a == fonge::float3::one()) );
                assert((a/fonge::float3::one() == a) );
                assert(a.dot(b) == b.dot(a));
                assert(a.dot(a) == a.len2());
                assert(a.dot(b) == a.x()*b.x() + a.y()*b.y() + a.z()*b.z());
                assert(a.cross(b).dot(b) == 0);
                assert(a.cross(b).dot(a) == 0);
                assert((a.cross(b) == -b.cross(a)) );
                assert((a.cross(b).dot(c) == b.cross(c).dot(a)));
                assert((a.cross(b).dot(c) == c.cross(a).dot(b)));
                assert((a.cross(b.cross(c)) == b*(a.dot(c)) - c*(a.dot(b))) );
                break;
            }

            case 2: {
                // +, -, *, /, dot(), cross() for float4
                float4 a(6, 7, 8, 9), b(10, 6, 7, 41), c(420, 5, 2, 6);
                // basic validation
                assert((a + b == float4(16, 13, 15, 50)) );
                assert((b - a == float4(4, -1, -1, 32)) );
                assert((a * b == float4(60, 42, 56, 9*41)) );
                assert((a/b == float4(0.6, 7./6., 8./7., 9./41.)) );
                assert(a.dot(b) == 60 + 42 + 56 + 9*41);
                assert(float4::one().dot(a.cross(b, c)) == -13561);
                // properties
                assert((a + b == b + a) );
                assert((a - b == -(b - a)) );
                assert((a - b == -b + a) );
                assert((a * b == b * a) );
                assert((a/a == float4::one()) );
                assert((a * 1/b == a/b) );
                assert((a * 1 == a) );
                assert((a * 0 == 0) );
                assert(a.dot(b) == b.dot(a));
                assert(a.dot(a) == a.len2());
                assert(a.dot(b) == a.x()*b.x() + a.y()*b.y() + a.z()*b.z() + a.w()*b.w());
                assert(a.cross(b, c).dot(a) == 0);
                assert(a.cross(b, c).dot(b) == 0);
                assert(a.cross(b, c).dot(c) == 0);
                assert((a.cross(b, c) == -b.cross(a, c)) );
                break;
            }

            case 3: {
                quat a = quat::from_angle_axis(67*DEG2RAD, float3(6, 7, 41).normalized());
                quat b = quat::from_angle_axis(41*DEG2RAD, float3(-9, 6, 9).normalized());
                quat c(float3::x_axis(), 0);
                quat d(float3::y_axis(), 0);

                assert(((c * d).vec.xyz() == float3::z_axis()) );
                auto tst = quat::from_angle_axis(90*DEG2RAD, float3::y_axis()).rotate(float3::x_axis());
                break;
            }
        }
    }
}