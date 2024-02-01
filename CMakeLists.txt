cmake_minimum_required(VERSION 3.26)
project(projectcpp)

set(CMAKE_CXX_STANDARD 17)


add_executable(
        projectcpp main.cpp
        BigFloat/bigfloat.cpp
        BigFloat/bigfloat.hpp
)
