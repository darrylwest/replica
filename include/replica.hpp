//
// Created by Darryl West on 1/27/22.
//

#pragma once
#ifndef REPLICA_HPP
#define REPLICA_HPP

#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "fmt/color.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <string>
#include <string_view>
#include <chrono>
#include <vector>
#include <filesystem>

#include "utils.hpp"

namespace replica {
    const char* APP_VERSION = "22.2.28";
    const char* BANNER = "Replica Exchange Service © 2022 Rain City Software";

    struct PollSpec {
        bool enabled {true};
        long interval {5000}; // millis
    };

    struct ReplicaSpec {
        std::string version;
        std::string name;
        std::vector<std::string> src_folders;
        std::vector<std::string> targets;
        bool compress {false};
        std::vector<std::string> compression_rules;
        bool encrypt {false};
        std::vector<std::string> encryption_rules;
        PollSpec poll_spec;
    };

    namespace fs = std::filesystem;
    using tp = std::chrono::system_clock::time_point;
    struct FileSpec {
        std::string filename;
        std::uintmax_t size;
        size_t last_modified;
        size_t last_replica;
        size_t last_scan;
        std::string sha;

        std::string to_string() {
            return fmt::format("{},{},{},{},{},{}", 
                this->filename, 
                this->size, 
                this->last_modified,
                this->last_replica,
                this->last_scan,
                this->sha
            );
        }
    };

    auto home_path() {
        auto path = std::string(std::getenv("HOME")) + std::string("/.replica");
        auto home = fs::path(path);

        if (!fs::exists(home)) {
            fmt::print("Create replica home: {}\n", path);
            fs::create_directory(home);
        }

        return home;
    }

    auto get_logger() {
        static const char *NAME = "replica-logger";

        auto logger = spdlog::get(NAME);

        // start the logger
        if (logger == NULL) {
            fs::path logfile = home_path();

            // TODO : if a replica.log.specs file exists, read params from it...

            logfile.append(std::string{"replica.log"});
            fmt::print("logfile : {} \n", logfile.string());

            const int max_size = 500000;
            const int max_files = 3;

            logger = spdlog::rotating_logger_mt(NAME, logfile, max_size, max_files);

            logger->info("Started rolling-logger with max size: {} bytes...", max_size);
        }

        return logger;
    }

    using svec = std::vector<std::string>;
    using fvec = std::vector<FileSpec>;
    bool include(const fs::path path, const svec extensions, const svec excludes) {
        if (extensions.size() == 0 && excludes.size() == 0) {
            return true;
        }

        const auto spath = path.string();
        for (auto const& exclude : excludes) {
            if (spath.find(exclude) != std::string::npos) {
                return false;
            }
        }

        return true;
    }

    // scan all files in the specified folder; return a vector of 
    fvec scan_files(const fs::path folder, const svec extensions, const svec excludes) {
        using namespace std::chrono;
        const auto logger = get_logger();
        logger->info("scan folder: {}", folder.string());

        // TODO: first, verify that the folder exists...

        auto files = fvec();

        for (auto const& file : fs::recursive_directory_iterator(folder)) {
            if (file.is_regular_file() && include(file.path(), extensions, excludes)) {
                auto spec = FileSpec();
                spec.filename = file.path();
                spec.size = file.file_size();
                spec.last_modified = utils::file_mod_time(file.path());

                spec.last_scan = utils::epoch_now();

                files.emplace_back(spec);
            }
        }

        logger->info("scan complete, files: {}", files.size());

        return files;
    }

    void scan_myfiles() {
        const auto logger = get_logger();
        const auto path = std::string_view("/usr/local/bin/");
        const auto folder = fs::path(path);

        const auto extensions = svec();
        const auto excludes = svec();
        const auto list = scan_files(path, extensions, excludes);

        for (auto file : list) {
            logger->info("{}", file.to_string());
        }
    }
}

#endif
