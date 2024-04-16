cmake_minimum_required(VERSION 3.17)
project(lesson01hw01)

set(CMAKE_CXX_STANDARD 14)


set(LOCAL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LOCAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} 
    ${LOCAL_SRC}/main.cpp  
    ${LOCAL_SRC}/matchbox.cpp
    ${LOCAL_SRC}/player.cpp
    ${LOCAL_SRC}/dice.cpp
    ${LOCAL_SRC}/game.cpp
    ${LOCAL_INCLUDE}/matchbox.h
    ${LOCAL_INCLUDE}/match.h
    ${LOCAL_INCLUDE}/dice.h
    ${LOCAL_INCLUDE}/player.h
    ${LOCAL_INCLUDE}/game.h
    )

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out)
