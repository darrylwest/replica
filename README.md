# Replica File Distribution Service

```
                   __ __                 __                __                
.----.-----.-----.|  |__|.----.---.-.   |  |--.---.-.----.|  |--.--.--.-----.
|   _|  -__|  _  ||  |  ||  __|  _  |   |  _  |  _  |  __||    <|  |  |  _  |
|__| |_____|   __||__|__||____|___._|(.)|_____|___._|____||__|__|_____|   __|
           |__|                                                      |__|   
```

## Overview

Replica is a file watching and replication service that monitors files on a server or laptop and distributes the files to
various target servers.  It is commonly used for simple remote backup but can also be used to develop multi-platform
targets with instant compile and test feedback.

## CMake & CLion

This project is based on manual editing of CMakeFiles.txt to comply with src/library/test/build folder structure.  Development 
is enabled for CLion but can be done in vim, vscode, or any editor.

## Branches

* main branch: this is the distribution branch.
* develop branch: this is the primary development branch.  It's merged to main usually through pull requests.

## Dependents

* cxxopts for command line opt parsing
* openSSL to encrypt files when necessary
* ?? for compression when necessary
* fswatch (or other watch lib) to monitor mac os or linux file systesms

## Package Management

[CPM?](https://github.com/cpm-cmake/CPM.cmake)

## Data Structs

### PollSpec

Used to define a file/folder polling interval and whether is should be enabled or disabled.

### ReplicaSpec

Defines files to watch and targets for replication.  Also includes poll spec to determine if polling is preferred it watcher.


### FileSpec

Specs on each watched file including modification date, size, sha sum, and the last time it was replicated.

## Notes

* no classes, just structs

### References

* [Building & Packaging](https://learning.oreilly.com/library/view/software-architecture-with/9781838554590/7f997c01-2634-4584-be95-0b068f448312.xhtml#uuid-f1312c0b-6145-4f6c-a1ea-16e37221eb42): Software Architecture with C++; info on CMake, CPack, Conan and Google Test
* [Mastering StdLib](https://learning.oreilly.com/library/view/professional-c-4th/9781119421306/c18.xhtml): Professional C++, 4th Edition; Lambdas, Function objects, RegEx, Ratios, Chrono, Random, Optional, Variant, Tuples, Filesystem
* [C++20 for Programmers](https://learning.oreilly.com/library/view/c-20-for-programmers/9780136905776/ch06.xhtml#ch06); The basics of c++20, Ranges, Modules, Containers
* [Modern C++ Programming Cookbook](https://learning.oreilly.com/library/view/modern-c-programming/9781800208988/Text/Chapter_1.xhtml#_idParaDest-18); 
  * lots of c++20 new features :Type aliases, Alias & Function templates, Ranges, Unnamed Namespaces, Structured binding/mult-return values, static cast.
  * Filesystem, Chrono, Containers
  * Catch2, [Google Test](https://google.github.io/googletest/reference/assertions.html)
  * gcovr

###### darryl.west | 2022.01.28

