cmake_minimum_required(VERSION 2.8.3)

project(pointer)

add_compile_options(-std=c++11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(call_by_value src/call_by_value.cpp)
add_executable(call_by_pointer src/call_by_pointer.cpp)
add_executable(call_by_reference src/call_by_reference.cpp)
add_executable(test src/test.cpp)
