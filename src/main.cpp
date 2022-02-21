
#include <iostream>
#include "replica.hpp"
#include "config.hpp"

int main(int argc, const char *argv[]) {
    replica::config::Config config = replica::config::parse(argc, argv);

    // TODO : move this part to process module to enable unit tests...
    if (config.skip) {
        return 0;
    } else if (config.dryrun) {
        std::cout << replica::BANNER << '\n';
        std::cout << "Version: " << replica::APP_VERSION << std::endl;

        // the ticker listens for changes to config and  if polling is enabled, queries files for changes
        std::cout << "start the ticker..." << '\n';

        // listen for signal events

        return 0;
    }

    return 0;
}
