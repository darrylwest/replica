
#include <iostream>
#include "replica.hpp"

int main(int argc, char *argv[]) {
    replica::Config config = replica::parse(argc, argv);

    std::cout << "dry run? " << config.dryrun << std::endl;
    std::cout << "replica version: " << replica::APP_VERSION << std::endl;

    return 0;
}

