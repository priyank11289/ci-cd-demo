# 

cmake_minimum_required(VERSION 3.16)

project(CICDDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Build with gcov coverage instrumentation" OFF)

if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(--coverage -O0 -g)
        add_link_options(--coverage)
    else()
        message(FATAL_ERROR "ENABLE_COVERAGE requires GCC or Clang")
    endif()
endif()

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
    test/test_coverage.cpp
    test/test_math.cpp
)

target_link_libraries(unit_tests
    PRIVATE
    math_utils
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(unit_tests)

if(ENABLE_COVERAGE)
    find_program(LCOV_EXECUTABLE lcov)
    find_program(GENHTML_EXECUTABLE genhtml)

    if(LCOV_EXECUTABLE AND GENHTML_EXECUTABLE)
        add_custom_target(coverage
            COMMAND ${CMAKE_CTEST_COMMAND} --test-dir ${CMAKE_BINARY_DIR} --output-on-failure
            COMMAND ${LCOV_EXECUTABLE} --rc branch_coverage=1 --ignore-errors mismatch --capture --directory ${CMAKE_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info
            COMMAND ${LCOV_EXECUTABLE} --rc branch_coverage=1 --ignore-errors unused --remove ${CMAKE_BINARY_DIR}/coverage.info "/usr/*" "*/_deps/*" "*/test/*" --output-file ${CMAKE_BINARY_DIR}/coverage.filtered.info
            COMMAND ${GENHTML_EXECUTABLE} --rc branch_coverage=1 ${CMAKE_BINARY_DIR}/coverage.filtered.info --output-directory ${CMAKE_BINARY_DIR}/coverage-report
            DEPENDS unit_tests
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Running tests and generating lcov coverage report"
        )
    else()
        message(WARNING "lcov/genhtml not found; install lcov to enable the coverage target")
    endif()
endif()
