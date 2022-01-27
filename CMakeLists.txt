cmake_minimum_required(VERSION 3.21)
project(replica)

set(CMAKE_CXX_STANDARD 20)

add_executable(replica src/main.cpp include/replica.hpp)
