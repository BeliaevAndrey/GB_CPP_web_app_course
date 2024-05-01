cmake_minimum_required(VERSION 3.6)
project(tic_tac_toe_client CXX)

set(INC ${CMAKE_SOURCE_DIR}/client/include)
set(SRC ${CMAKE_SOURCE_DIR}/client/src)

SET(NTTC_SRC
    ${SRC}/client.cpp
    ${SRC}/gamemanager.cpp
    ${SRC}/simpleboard.cpp
    ${SRC}/consoleplayer.cpp
    ${SRC}/consolegame.cpp
)

SET(NTTC_INC
    ${INC}/board.h
    ${INC}/consolegame.h
    ${INC}/player.h
    ${INC}/consoleplayer.h
    ${INC}/gamemanager.h
    ${INC}/simpleboard.h
)

add_executable(${PROJECT_NAME} ${NTTC_SRC} ${NTTC_INC})
target_include_directories(${PROJECT_NAME} PUBLIC include)
