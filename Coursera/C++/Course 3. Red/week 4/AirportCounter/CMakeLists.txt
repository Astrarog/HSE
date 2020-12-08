cmake_minimum_required(VERSION 3.5)

project(task LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp test_runner.h profile.h)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENTIONS OFF)
