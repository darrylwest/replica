cmake_minimum_required(VERSION 3.2)

project(replica)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(REPLICA_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(REPLICA_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(REPLICA_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(REPLICA_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/replica)

include_directories(${REPLICA_INSTALL_INCLUDE_DIR})
include_directories(${REPLICA_HEADERS_DIR})

add_subdirectory(src)
# add_subdirectory(test)


