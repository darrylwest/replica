cmake_minimum_required(VERSION 3.16)
project(replica VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GoogleTest)

add_compile_options(-Wall -Wextra -pedantic -Werror -O3)

add_executable(replica src/main.cpp)
target_include_directories(replica PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
