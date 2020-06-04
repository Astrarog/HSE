cmake_minimum_required(VERSION 3.5)

project(untitled15 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(untitled15 main.cpp query.cpp query.h responses.cpp responses.h bus_manager.cpp bus_manager.h)
