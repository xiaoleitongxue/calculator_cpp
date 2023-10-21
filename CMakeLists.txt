cmake_minimum_required(VERSION 3.20.0)
project(expression_calculator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(calculator calculator.cpp)
add_executable(expression_calculator expression_calculator.cpp)
add_executable(char_input_test char_input_test.cpp)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
