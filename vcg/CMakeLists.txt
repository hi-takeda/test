cmake_minimum_required(VERSION 2.8.3)

project(vcg)

add_compile_options(-std=c++11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(VCG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/vcglib-1.0.1)

include_directories(${VCG_INCLUDE_DIR})

add_executable(
  test
  ${SRC_DIR}/test.cpp
  )

add_executable(
  create_destroy_mesh
  ${SRC_DIR}/create_destroy_mesh.cpp
  )
