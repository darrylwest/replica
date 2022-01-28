#
# 2022-01-28 09:48:22 dpw
#
cmake_minimum_required(VERSION 3.16)
project(replica VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GoogleTest)

add_compile_options(-Wall -Wextra -pedantic -Werror -O3)

project(replica VERSION 1.0.1 LANGUAGES CXX)
add_executable(replica src/main.cpp) # should add new source files now...
target_include_directories(replica PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# could define the file list this way, but not recommended
# file(GLOB_RECURSE SRC_FILES src/*.cpp)
# add_executable(replica ${SRC_FILES})

# could also add a library
# add_library(blah STATIC blah/Blah.cpp)
# add_subdirectory()
# @see this: https://www.youtube.com/watch?v=mKZ-i-UfGgQ

# find_package : will need this for OpenSSL, Compress, ssh etc.
# target_link_libraries(replica PUBLIC ${MY_LIB})
