
#include <iostream>
#include "replica.hpp"

int main(int argc, char *argv[]) {
    replica::Config config = replica::parse(argc, argv);

    // TODO : move this part to process module to enable unit tests...
    if (config.skip) {
        return 0;
    } else if (config.dryrun) {
        std::cout << replica::BANNER << '\n';
        std::cout << "Version: " << replica::APP_VERSION << std::endl;

        // show the complete config...
        std::cout << "Config: name: " << config.name << std::endl;
        std::cout << "Config: home: " << config.replica_home << std::endl;
        std::cout << "Config: dry-run: " << config.dryrun << std::endl;
        std::cout << "Poll.enabled: " << config.poll_spec.enabled << std::endl;
        std::cout << "Config: file: " << config.config_file << std::endl;

        return 0;
    }

    return 0;
}
