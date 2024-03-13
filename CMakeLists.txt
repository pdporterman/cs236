cmake_minimum_required(VERSION 3.26)
project(cs236)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project1)

add_executable(cs236
        Project/Database.h
        Project/Tuple.h
        Project/Interpreter.h
        Project/Parameter.h
        Project/Predicate.h
        Project/Relation.h
        Project/Scheme.h
        Project/DatalogProgram.h
        Project/main.cpp)
