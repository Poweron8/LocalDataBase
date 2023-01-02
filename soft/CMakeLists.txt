cmake_minimum_required(VERSION 3.5)

project(LocalDataBase LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(commands)
file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)
file(GLOB COMMANDS commands/*.cpp commands/*.h)
add_executable(LocalDataBase ${SOURCES} ${HEADERS} ${COMMANDS})
