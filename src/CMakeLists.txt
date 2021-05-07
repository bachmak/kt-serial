add_library(kt_serial INTERFACE)

target_include_directories(
    kt_serial INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(kt_serial INTERFACE /W4 /WX)
else()
    target_compile_options(
        kt_serial INTERFACE -Wall -Wextra -pedantic -Werror -Wsign-conversion
    )
endif()
