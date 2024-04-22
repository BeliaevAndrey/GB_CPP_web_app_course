cmake_minimum_required(VERSION 3.17)
project(gameapp LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR}/gamelib/include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} gamelib)
