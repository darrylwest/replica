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
#include "ticker.hpp"
#include "config.hpp"

namespace replica {
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

        if (extensions.size() == 0) return true;

        const auto ext = path.extension();
        std::cout << path.string() << ", ext: " << ext;
        for (auto const& in : extensions) {
            if (in == ext) {
                return true;
            }
        }

        return false;
    }

    // scan all files in the specified folder; return a vector of included files
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

    void start_scan(replica::config::Config config) {
        const auto logger = get_logger();

        logger->info("start the ticker with interval: {}", config.interval);

        const svec excludes{"fmt/", "cxxopts.hpp", "catch.hpp", ".git/", "/build/"};
        const svec extensions{".hpp", ".cpp"};

        auto last_scan = fvec();
        
        for (const auto src : config.sources) {
            auto files = scan_files(fs::path(src), extensions, excludes);
            for (const auto file : files) {
                last_scan.push_back(file);
            }
        }

        std::thread t = replica::ticker::start(config.interval, [&](const size_t tick) -> bool {
            logger->info("tick {}", tick);

            for (auto file : last_scan) {
                logger->info("{} {} {}", file.filename, file.last_modified, file.size);
            }

            logger->flush();
            return true;
        });

        t.join();
    }
}

#endif
