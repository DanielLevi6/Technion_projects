cmake_minimum_required(VERSION 3.0.0)
project(part2 VERSION 0.1.0 LANGUAGES C)

set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror -DNDEBUG")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

add_executable(mtm_buggy mtm_buggy.c)