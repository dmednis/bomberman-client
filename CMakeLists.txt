cmake_minimum_required(VERSION 3.8)
project(bomberman_client)

set(CMAKE_C_STANDARD 90)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${MyProject_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES main.c helpers.h helpers.c constants.h drawing.h drawing.c)
add_executable(bomberman_client ${SOURCE_FILES})
target_link_libraries(bomberman_client ${CURSES_LIBRARIES})
target_link_libraries(bomberman_client ${SDL2_LIBRARY})

add_executable(draw_test draw_test.c)
target_link_libraries(draw_test SDL2 SDL2_ttf SDL2_image)
