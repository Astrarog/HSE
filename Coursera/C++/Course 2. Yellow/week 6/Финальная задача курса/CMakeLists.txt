cmake_minimum_required(VERSION 3.5)

project(task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp
    condition_parser.cpp condition_parser_test.cpp condition_parser.h
    token.cpp token.h
    date.cpp date.h
    node.cpp node.h
    database.cpp database.h database_test.cpp
    test_runner.h)
