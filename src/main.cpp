//
// dpw
//

#include <iostream>

#include "replica.hpp"
#include "config.hpp"

int main(int argc, const char *argv[]) {
    auto config = replica::config::parse(argc, argv);

    // TODO : move this part to process module to enable unit tests...
    if (config.skip) {
        return 0;
    } else if (config.dryrun) {
        auto style = fg(fmt::color::lime) | fmt::emphasis::bold;
        fmt::print(style, "{}, Version: {}\n", replica::BANNER, replica::APP_VERSION);

        auto logger = replica::create_logger();
        // the ticker listens for changes to config and  if polling is enabled, queries files for changes

        replica::scan_myfiles();

        fmt::print("start the ticker... \n");

        // listen for signal events

        return 0;
    }

    return 0;
}
