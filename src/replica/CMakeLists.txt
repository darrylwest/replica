cmake_minimum_required(VERSION 3.2)
project(division C CXX)

set(SOURCE_FILES
    replica.hpp
    replica.cpp
)

add_library(replica SHARED STATIC ${SOURCE_FILES})

install(TARGETS replica DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES replica.hpp DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
