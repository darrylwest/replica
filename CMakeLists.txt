cmake_minimum_required(VERSION 3.14)

project(replica VERSION 0.1.0 LANGUAGES CXX)

add_libary(replicalib
  include/replica.hpp
)

target_include_directories(replicalib PUBLIC include)

add_executable(replicacli src/main.cpp)
target_link_libraries(replacacli PRIVATE replicalib)
