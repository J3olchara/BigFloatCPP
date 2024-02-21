cmake_minimum_required(VERSION 3.20)
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

add_subdirectory(tests)

add_executable(${This}
        ${Sources}
        ${Headers}
)

target_link_libraries(${This} PUBLIC
    big
)
target_include_directories(${This} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(run_tests
        COMMAND tests
        DEPENDS tests
        COMMENT "Running tests"
)

add_dependencies(${This}
    run_tests
)