#!/usr/bin/env bash
# dpw@Darryls-iMac.localdomain
# 2022-01-28 01:41:38
#


set -eu

function clean() {
  printf "clean all from build folder...\n"
  /bin/rm -fr build
}

function config() {
  [ -f build/Makefile ] || {
    printf "create build folder...\n"
    /bin/rm -fr build
    mkdir build && cd build && cmake ../
  }
}

function build() {
  cd build 
  make
}

function run() {
  printf "run the examples...\n"
  ./replica --version
  ./replica --help
  ./replica --dryrun
}

echo "program: $0"
case $0 in
  *clean)
    clean
    ;;
  *)
    config && build && run
    ;;
esac

[ $? ] && printf "Ok\n" || printf "Failed...\n"

exit 0

