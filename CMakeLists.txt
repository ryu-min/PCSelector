cmake_minimum_required(VERSION 3.5)

project(PCSelector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

file (GLOB_RECURSE PROJECT_SOURCES
            "${SOURCE_DIR}/*.hpp"
            "${SOURCE_DIR}/*.cpp"
            "${SOURCE_DIR}/json/*.hpp"
            )

add_executable(PCSelector ${PROJECT_SOURCES})
