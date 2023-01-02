cmake_minimum_required(VERSION 3.5)
project(regression_tests)

enable_testing()

find_package(GTest REQUIRED)
set(PROJECT_ADDR ${CMAKE_SOURCE_DIR}/../soft)

file (GLOB TESTS *.h *.cpp)
file (GLOB_RECURSE SOURCES ${PROJECT_ADDR}/*.cpp)
file (GLOB_RECURSE HEADERS ${PROJECT_ADDR}/*.h)
list(REMOVE_ITEM SOURCES ${PROJECT_ADDR}/main.cpp)

add_executable(regression_tests ${TESTS} ${COMMANDS} ${SOURCES} ${HEADERS})

target_link_libraries(regression_tests GTest::gtest GTest::gtest_main)

add_test(NAME regression_tests COMMAND regression_tests)


