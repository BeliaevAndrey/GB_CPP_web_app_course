cmake_minimum_required(VERSION 3.17)
project(gamelib LANGUAGES CXX)

add_library(
  ${PROJECT_NAME} SHARED
  src/matchbox.cpp
  src/player.cpp
  src/dice.cpp
  src/game.cpp
  include/matchbox.h
  include/match.h
  include/dice.h
  include/player.h
  include/game.h)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME gamelib)

set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
                                                 ${CMAKE_BINARY_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC include)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/out)

install(FILES ${CMAKE_SOURCE_DIR}/scripts/starter.sh
        DESTINATION ${CMAKE_SOURCE_DIR}/out)

install(CODE "execute_process(
    COMMAND bash -c \"cd ../out; chmod u+x starter.sh\"
    )")
