//
//
//

#pragma once
#ifndef REPLICA_TICKER_HPP
#define REPLICA_TICKER_HPP

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <functional>

namespace replica {
    namespace ticker {
        void run(const int interval, const std::function<bool(const size_t)> fn) {
            size_t tick = 0;

            do {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            } while (fn(++tick));
        }

        auto start(const int interval, const std::function<bool(const size_t)> fn) {
            std::thread t(run, interval, fn);

            return t;
        };
    }
}
#endif