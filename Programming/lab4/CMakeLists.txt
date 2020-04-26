cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lab4 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/dev/lib/include")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/dev/lib/lib")

#find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} main.cpp flower.cpp flower.hpp sortings.hpp tmeasure.hpp search.hpp
 hash.hpp output.hpp random.hpp)

#target_link_libraries(${PROJECT_NAME} Boost::Boost)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
