cmake_minimum_required(VERSION 3.10.0)
project(fonge_math VERSION 0.1.0 LANGUAGES C CXX)

add_library(fonge_math INTERFACE)
target_include_directories(fonge_math INTERFACE "include/" "external/simde/")

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
