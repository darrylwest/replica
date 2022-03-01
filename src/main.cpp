//
// dpw
//

#include <iostream>
#include <thread>

#include "replica.hpp"
#include "config.hpp"

int main(int argc, const char *argv[]) {
    const auto config = replica::config::parse(argc, argv);

    if (config.skip) {
        return 0;
    } else if (config.dryrun) {
        const auto style = fg(fmt::color::lime) | fmt::emphasis::bold;
        fmt::print(style, "{}, Version: {}\n", replica::BANNER, replica::APP_VERSION);

        replica::start_scan(config);
    }

    return 0;
}
