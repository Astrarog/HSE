cmake_minimum_required(VERSION 3.5)

project(task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task main.cpp stack_vector.h test_runner.h profile.h)
