cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lab4 LANGUAGES CXX)

set(BOOST_INCLUDEDIR "C:/Boost/boost_1_72_0/")
set(BOOST_ROOT "C:/Boost/boost_1_72_0/")
set(BOOST_LIBRARYDIR "C:/Boost/boost_1_72_0/stage/lib")

find_package(Boost REQUIRED)
if(Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIR})
    add_definitions( "-DHAS_BOOST" )

    add_executable(${PROJECT_NAME} main.cpp flower.cpp flower.hpp sortings.hpp tmeasure.hpp search.hpp
     hash.hpp output.hpp random.hpp)

    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
endif()
