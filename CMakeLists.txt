cmake_minimum_required(VERSION 3.26)
project(cs236)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project1)

add_executable(cs236
        Project1/main.cpp
        Project1/Scanner.h
        Project1/Token.h)
