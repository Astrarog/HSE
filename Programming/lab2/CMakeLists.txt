cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lab2 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp flower.cpp flower.hpp sortings.hpp tmeasure.hpp search.hpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
