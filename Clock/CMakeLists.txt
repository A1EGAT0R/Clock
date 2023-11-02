cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDART 14)

project(clock)

set(SOURCE_MAIN main.cpp)
set(SOURCE_CLASS Time.cpp Clock.cpp)
set(HEAD_CLASS Time.hpp Clock.hpp)

add_library(classes STATIC ${HEAD_CLASS} ${SOURCE_CLASS})

add_executable(main ${SOURCE_MAIN})

target_link_libraries(main classes)


