cmake_minimum_required(version 3.28.3)

project(stack_allocator version 1.0 languages C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER /usr/bin/clang)

add_executable(
    src/main.c
    src/allocator.c
)

