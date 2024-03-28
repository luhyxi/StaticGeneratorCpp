cmake_minimum_required(VERSION 3.29)
project(DeGen)

set(CMAKE_CXX_STANDARD 23)

add_executable(DeGen main.cpp
        Entities/MDParser.cpp)
