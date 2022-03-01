//
// dpw
//

#include <iostream>
#include <thread>

#include "replica.hpp"
#include "config.hpp"
#include "ticker.hpp"

bool tick_handler(const size_t tick) {
    const auto logger = replica::get_logger();
    logger->info("tick {}", tick);

    std::cout << "run the thread loop, tick: " << tick << std::endl;

    return true;
}

void start_scan(replica::config::Config config) {
    const auto logger = replica::get_logger();

    logger->info("start the ticker with interval: {}", config.interval);

    std::thread t = replica::ticker::start(config.interval, tick_handler);

    t.join();
}

int main(int argc, const char *argv[]) {
    const auto config = replica::config::parse(argc, argv);

    // TODO : move this part to process module to enable unit tests...
    if (config.skip) {
        return 0;
    } else if (config.dryrun) {
        const auto style = fg(fmt::color::lime) | fmt::emphasis::bold;
        fmt::print(style, "{}, Version: {}\n", replica::BANNER, replica::APP_VERSION);

        start_scan(config);

        return 0;
    }

    return 0;
}
