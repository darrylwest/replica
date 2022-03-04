# Replica Sync Service

```
 ___          _ _           ___                ___              _
| _ \___ _ __| (_)__ __ _  / __|_  _ _ _  __  / __| ___ _ ___ _(_)__ ___
|   / -_) '_ \ | / _/ _` |_\__ \ || | ' \/ _|_\__ \/ -_) '_\ V / / _/ -_)
|_|_\___| .__/_|_\__\__,_(_)___/\_, |_||_\__(_)___/\___|_|  \_/|_\__\___|
        |_|                     |__/

     01110010 01100101 01110000 01101100 01101001 01100011 01100001
```

## Overview

Replica is a file watching and replication service that monitors files on a server or laptop and distributes the files to
various target servers.  It is commonly used for simple remote backup but can also be used to develop multi-platform
targets with instant compile and test feedback.

## Usage

```
replica  \
  --sources src,include,test \
  --extensions .hpp,.cpp \
  --excludes 'cxxopts.hpp,fmt/,catch.hpp,.git,/build/' \
  --cmd make`
```

### Help

```
Replica Exchange Service © 2022 Rain City Software
Usage:
  ./build/replica [OPTION...]

  -v, --version         Show the current version
  -h, --help            Show this help
  -d, --dryrun          Just parse but don't run replica
  -c, --config arg      The configuration file
  -i, --interval arg    Specify the loop inteval in milliseconds
  -s, --sources arg     A comma delimited list of source folders to watch
  -e, --extensions arg  A comma delimited list of extensions, e.g.,
                        .hpp,cpp,.c
  -x, --excludes arg    A comma delimited list of files/folders to exclude
      --cmd arg         A system command to run when a watched file is
                        modified
```

### Replica Ticker Loop

_TBD_

## CMake

This project is based on manual editing of CMakeFiles.txt to comply with src/library/test/build folder structure.  Development 
is enabled for CLion but can be done in vim, vscode, or any editor.

## Branches

* main branch: this is the distribution branch.
* develop branch: this is the primary development branch.  It's merged to main usually through pull requests.

_Custom branches are also available for specific builds_

## Package Management (_future_)

[CPM?](https://github.com/cpm-cmake/CPM.cmake)

## Data Structs

* Config
* FileSpec

## Notes

* cpp 20
* build and tested for linux (debian) with gcc 10.2 and mac with clang 13
* structs and closures but no classes

## Dependencies

std=c++20
CMake 3.16
Debian 11, gcc 10
osX 12, Apple Clang 13.0.0, darwin 21.3

_TODO : write a script to pull, build and install all deps to an internal (or cached) deps folder..._

* [ ] fmt/format - download, build and install
* [ ] spdlog - download, build and install
* [ ] threads - available with gcc
* [ ] cxxopts.hpp - in the include folder
* [ ] catch2 - included in test folder
* [ ] json - nlohmann-json ; brew install nlohmann-json ; debian: download, build and install

_Future dependencies for multi-machine implementations, backups, etc._

* [ ] openssl - install
* [ ] boost - v1.74 ; apt-get install libboost-all-dev / brew install boost

_Consider using [message-pack](https://github.com/msgpack/msgpack-c/tree/cpp_master) to replace/augment json encoding..._

### References

* [Building & Packaging](https://learning.oreilly.com/library/view/software-architecture-with/9781838554590/7f997c01-2634-4584-be95-0b068f448312.xhtml#uuid-f1312c0b-6145-4f6c-a1ea-16e37221eb42): Software Architecture with C++; info on CMake, CPack, Conan and Google Test
* [Mastering StdLib](https://learning.oreilly.com/library/view/professional-c-4th/9781119421306/c18.xhtml): Professional C++, 4th Edition; Lambdas, Function objects, RegEx, Ratios, Chrono, Random, Optional, Variant, Tuples, Filesystem
* [C++20 for Programmers](https://learning.oreilly.com/library/view/c-20-for-programmers/9780136905776/ch06.xhtml#ch06); The basics of c++20, Ranges, Modules, Containers
* [Modern C++ Programming Cookbook](https://learning.oreilly.com/library/view/modern-c-programming/9781800208988/Text/Chapter_1.xhtml#_idParaDest-18); 
  * lots of c++20 new features :Type aliases, Alias & Function templates, Ranges, Unnamed Namespaces, Structured binding/mult-return values, static cast.
  * Filesystem, Chrono, Containers
  * [Google Test](https://google.github.io/googletest/reference/assertions.html)
  * [Catch2](https://catch2.docsforge.com/) -- single hpp install (v2/v2.13.2 prior to V3)
  * gcovr
* [CCache](https://ccache.dev/)
* [Speed Log spdlog Fast c++ logger](https://github.com/gabime/spdlog)
* [Build2 Toolchain](https://www.build2.org/)

###### darryl.west | 2022.03.01
