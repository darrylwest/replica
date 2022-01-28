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

## Data Structs


## Notes

* no classes, just structs

###### darryl.west | 2022.01.28

