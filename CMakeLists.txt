project(dvdpong)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB SOURCES "src/*.cpp")

add_executable(dvdpong ${SOURCES})
target_link_libraries(dvdpong sfml-graphics sfml-system sfml-window)