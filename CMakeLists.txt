cmake_minimum_required(VERSION 3.22)
project(infix_to_postfix_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(infix_to_postfix_project
        main.cpp
        expression.cpp)
