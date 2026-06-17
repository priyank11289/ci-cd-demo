# 

cmake_minimum_required(VERSION 3.16)

project(CICDDemo)

set(CMAKE_CXX_STANDARD 17)

# Production library
add_library(math_utils
    src/math_utils.cpp
)

target_include_directories(math_utils PUBLIC src)

# Main application
add_executable(app
    src/main.cpp
)

target_link_libraries(app PRIVATE math_utils)

# --------------------------
# Unit Tests
# --------------------------

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
    test/test_math.cpp
)

target_link_libraries(unit_tests
    PRIVATE
    math_utils
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(unit_tests)