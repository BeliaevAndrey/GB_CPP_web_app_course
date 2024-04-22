cmake_minimum_required(VERSION 3.17)
project(lesson02hw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(gameapp)
add_subdirectory(gamelib)

add_dependencies(gameapp gamelib)
