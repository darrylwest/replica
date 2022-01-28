#!/usr/bin/env bash
# dpw@Darryls-iMac.localdomain
# 2022-01-28 01:41:38
#

set -eu

function config() {
  (
    [ -d build ] || {
      mkdir build
      cd build
      cmake ..
    }
  )
}

function build() {
  (
    cd build 
    make
  )
}

function run() {
  (
    cd build 
    ./replica --version
    ./replica --help
    ./replica --dryrun
  )
}

config && build && run

[ $? ] && echo "Ok" || echo "Failed"
exit 0

