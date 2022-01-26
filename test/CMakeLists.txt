cmake_minimum_required(VERSION 3.2)
project(replica_tests)

add_subdirectory(lib/googletest)

include_directories(${DIVISION_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/replica_tests.cpp)

add_executable(replica_tests ${SOURCE_FILES})
target_link_libraries(replica_tests replica gtest)
install(TARGETS replica_tests DESTINATION bin)

