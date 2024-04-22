cmake_minimum_required(VERSION 3.17)
project(gameapp LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR}/gamelib/include)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} gamelib)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/out)

# install(FILES ${CMAKE_SOURCE_DIR}/scripts/starter.sh
#         DESTINATION ${CMAKE_SOURCE_DIR}/out)

# install(CODE "execute_process(
#     COMMAND bash -c \"cd ../out; chmod u+x starter.sh\"
#     )")
