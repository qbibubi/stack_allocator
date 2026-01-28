cmake_minimum_required(VERSION 4.2)

project(stack_allocator VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER /usr/bin/clang)

add_executable(allocator
    main.c
    src/allocator.c
)

