#!/usr/bin/env bash
# dpw@Darryls-iMac.localdomain
# 2022-01-28 01:41:38
#


set -eu

clean() {
  printf "clean all from build folder...\n"
  /bin/rm -fr build
}

config() {
  (
    [ -f build/Makefile ] || {
      printf "create build folder...\n"
      /bin/rm -fr build
      cmake -S . -B build 
    }
  )
}

run() {
  (
    printf "run the examples...\n"
    cd build 
    ./replica --version
    ./replica --help
    ./replica --dryrun
  )
}

watch() {
  printf "watching from pid: $$\n"
  watchexec -c -d 250 -e .cpp,.hpp,.txt -p -i build -w ./ ./mk
}

run_tests() {
  ./build/test/replica_unit_tests --durations yes
}


echo "program: $0"
case $0 in
  *watch)
    watch
    ;;
  *build)
    cmake -S . -B build 
    ;;
  *clean)
    clean && config
    ;;
  *clean-mk)
    time ( clean && config && build && run && run_tests )
    ;;
  *mk)
    config && cmake --build build && run_tests
    ;;
  *run)
    ./build/replica -i 2500 -s src,include,test -e .hpp,.cpp -x 'cxxopts.hpp,fmt/,catch.hpp'
    ;;
  *)
    config && build && run && run_tests
    ;;
esac

[ $? ] && printf "Ok\n" || printf "Failed...\n"

exit 0

