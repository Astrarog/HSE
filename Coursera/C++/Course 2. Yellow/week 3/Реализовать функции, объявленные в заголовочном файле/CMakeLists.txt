cmake_minimum_required(VERSION 3.5)

project(task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp sum_reverse_sort.h sum_reverse_sort.cpp)
