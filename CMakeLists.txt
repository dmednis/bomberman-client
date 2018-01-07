cmake_minimum_required(VERSION 3.8)
project(cmake_build_debug)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c helpers.h helpers.c)
add_executable(cmake_build_debug ${SOURCE_FILES})