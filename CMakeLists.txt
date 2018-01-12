cmake_minimum_required(VERSION 3.8)
project(bomberman_client)

set(CMAKE_C_STANDARD 90)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES main.c helpers.h helpers.c constants.h drawing.h drawing.c)
add_executable(bomberman_client ${SOURCE_FILES})

target_link_libraries(bomberman_client ${CURSES_LIBRARIES})