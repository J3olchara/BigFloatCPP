cmake_minimum_required(VERSION 3.26)
project(projectcpp)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()


add_executable(
        ${PROJECT_NAME} main.cpp
        BigFloat/bigfloat.cpp
        BigFloat/bigfloat.hpp
)

