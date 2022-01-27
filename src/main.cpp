
#include <iostream>
#include "../include/replica.hpp"

int main(int argc, char *argv[]) {
    std::cout << replica::BANNER << '\n';
    std::cout << "Version: " << replica::APP_VERSION << std::endl;

    replica::Config config = replica::parse(argc, argv);

    std::cout << "Config: dry-run: " << config.dryrun << std::endl;

    return 0;
}
