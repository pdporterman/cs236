cmake_minimum_required(VERSION 3.26)
project(cs236)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project1)

add_executable(cs236
        Project3/Database.h
        Project3/Tuple.h
        Project3/Interpreter.h
        Project3/Parameter.h
        Project3/Predicate.h
        Project3/Relation.h
        Project3/Scheme.h
        Project3/DatalogProgram.h
        Project3/main.cpp)
