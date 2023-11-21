cmake_minimum_required(VERSION 3.18)

project(level-01 LANGUAGES CXX)

add_executable(level-01 main.cpp)

add_subdirectory(comparing)
add_subdirectory(unit-tests)