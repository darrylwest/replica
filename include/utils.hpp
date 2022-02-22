

#pragma once
#ifndef REPLICA_UTILS_HPP
#define REPLICA_UTILS_HPP

#include <string>
#include <chrono>
#include <vector>
#include <filesystem>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>

namespace utils {
    size_t epoch_now() {
        const auto now = std::chrono::system_clock::now();
        const auto epoch = now.time_since_epoch();
        const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);

        return seconds.count();
    }

    namespace fs = std::filesystem;
    size_t file_mod_time(const fs::path path) {
        struct stat result;

        if (stat(path.c_str(), &result) == 0) {
            auto mod_time = result.st_mtime;
            return mod_time;
        }

        return 0;
    }

    /* will not compile on mac with g++
    size_t convert_file_time(const fs::file_time_type ftime) {
        return std::chrono::system_clock::to_time_t(
            std::chrono::file_clock::to_sys(ftime)
        );
    }
    */
}

#endif