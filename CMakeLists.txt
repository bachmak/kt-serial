cmake_minimum_required(VERSION 3.16)

project(Kt-Serial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(KTSERIAL_BUILD_TESTS "Build tests" ON)

add_subdirectory(src)

if(KTSERIAL_BUILD_TESTS)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(tests)
    message("build kt-serial tests")
else()
    message("skip kt-serial tests")
endif()
