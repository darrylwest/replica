cmake_minimum_required(VERSION 3.21)
project(replica LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# include_directories(include)
add_compile_options(-Wall -Wextra -pedantic -Werror -O3)

add_executable(replica src/main.cpp)
