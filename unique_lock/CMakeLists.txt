cmake_minimum_required(VERSION 2.8.3)
project(main)
add_compile_options(-std=c++11)
add_executable(main main.cpp)
target_link_libraries(main pthread)
