cmake_minimum_required(VERSION 3.10.0)
project(fonge_math VERSION 0.1.0 LANGUAGES C CXX)

add_library(fonge_math INTERFACE)
target_include_directories(fonge_math INTERFACE "include/" "external/simde/")

include(CTest)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(testing tests.cpp)
target_link_libraries(testing PRIVATE fonge_math)

add_test(NAME float2_arithmetic COMMAND testing 0)
add_test(NAME float3_arithmetic COMMAND testing 1)
add_test(NAME float4_arithmetic COMMAND testing 2)
add_test(NAME quat_arithmetic COMMAND testing 3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
