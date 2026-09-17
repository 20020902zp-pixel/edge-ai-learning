cmake_minimum_required(VERSION 3.16)

project(day04_library_demo)

add_library(math_utils
    src/math_utils.cpp
)

target_include_directories(math_utils
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(demo
    app/main.cpp
)

target_link_libraries(demo
    PRIVATE
    math_utils
)