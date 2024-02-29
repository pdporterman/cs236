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
        Project2/main.cpp
        Project2/Parameter.h
        Project2/Predicate.h
        Project2/Rule.h
        Project2/DatalogProgram.h
        lab3/main.cpp
        lab3/Scheme.h
        lab3/Tuple.h
        lab3/Relation.h)
