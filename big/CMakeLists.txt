cmake_minimum_required(VERSION 3.26)
project(projectcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(This big)

set(Sources
    bigfloat.cpp
)
set(Headers
    bigfloat.hpp
)

add_library(${This} SHARED
    ${Sources}
    ${Headers}
)