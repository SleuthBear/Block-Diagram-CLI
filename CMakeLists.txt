cmake_minimum_required(VERSION 3.29)
project(BDCLI)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        Block.cpp
        LoopBack.cpp
        Arrow.cpp
        VArrow.cpp
        keyValues.cpp
        keyValues.h)
