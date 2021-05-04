cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sandbox sandbox.cpp)

target_include_directories(
    sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(sandbox PRIVATE /W4 /WX)
else()
    target_compile_options(
        sandbox PRIVATE -Wall -Wextra -pedantic -Werror -Wsign-conversion
    )
endif()
