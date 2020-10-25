
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(oopVariant11 LANGUAGES CXX)

add_executable(${PROJECT_NAME} "main.cpp" "myclass.cpp" "myclass.hpp" "countOnes.cpp" "countOnes.hpp")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)


set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

include(CheckCXXSourceCompiles)

check_cxx_source_compiles("int main(){return __builtin_popcountll(1) ;}" HAVE_POPCOUNTLL)

configure_file(config_intrinsic.hpp.in include/config-files/config.hpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
