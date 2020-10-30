cmake_minimum_required(VERSION 3.17)
project(fullmacro C)

set(CMAKE_C_STANDARD 11)

add_library(
        fullmacro
        fullmacro/fullmacro.c
        fullmacro/fullmacro.h
        fullmacro/common_bool.h
        fullmacro/fullmacro.c
        fullmacro/fullmacro.h
        fullmacro/infer.h
        fullmacro/shut_up.h
        fullmacro/version.h
)

add_executable(fullmacro_test main.c)

target_link_libraries(fullmacro_test fullmacro)