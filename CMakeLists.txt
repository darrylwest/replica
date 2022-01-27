cmake_minimum_required(VERSION 3.21)
project(replica)

set(CMAKE_CXX_STANDARD 20)

# include_directories(include)

add_executable(replica src/main.cpp include/replica.hpp)
