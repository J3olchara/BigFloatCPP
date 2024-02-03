cmake_minimum_required(VERSION 3.26)
project(projectcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(This Project)

option(BUILD_GMOCK "Add GMock for testing" OFF)

set(Sources
    main.cpp
)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/big
)

add_executable(${This}
    ${Sources}
    ${Headers}
)
add_subdirectory(tests)

target_link_libraries(${This} PUBLIC
    big
)
target_include_directories(${This} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
