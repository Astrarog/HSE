cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(Deblur LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenCV 4.0.0 REQUIRED)

add_executable(${PROJECT_NAME}
    "main.cpp" "deblur.hpp" "deblur.cpp")

target_link_libraries(${PROJECT_NAME} OpenCV::OpeCV)

target_compile_features(${PROJECT_NAME}
    PUBLIC cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENTIONS OFF)
