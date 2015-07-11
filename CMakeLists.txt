cmake_minimum_required(VERSION 3.2)
project(bogocrypt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(bogocrypt ${SOURCE_FILES} bogocrypt.h bogocrypt.c)