cmake_minimum_required(VERSION 3.26)
project(cs236)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project1)

add_executable(cs236
        Project1/main.cpp
        Project1/Scanner.h
        Project1/Token.h
        lab2/main.cpp
        lab2/Scanner.h
        lab2/Parser.h
        Project2/Token.h
        Project2/main.cpp)
