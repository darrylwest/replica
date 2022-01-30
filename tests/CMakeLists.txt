#
# 2022-01-28 09:48:22 dpw
#
cmake_minimum_required(VERSION 3.16)

project(replica_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror -O3)

add_executable(${PROJECT_NAME} main.cpp) # should add new source files now...
target_include_directories(replica_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

