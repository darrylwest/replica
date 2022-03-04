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
#include <cstdlib>

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
    using pvec = std::vector<fs::path>;

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
        logger->debug("scan folder: {}", folder.string());

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

        logger->debug("file count: {}", files.size());
        for (const auto &file : files) {
            logger->debug("{} {} {}", file.filename, file.last_modified, file.size);
        }

        return files;
    }

    fvec scan_folders(const svec folders, const svec extensions, const svec excludes) {
        auto files = fvec();

        for (const auto &src : folders) {
            auto list = scan_files(fs::path(src), extensions, excludes);
            for (const auto &file : list) {
                files.push_back(file);
            }
        }

        return files;
    }

    svec validate_folders(const svec sources) {
        auto folders = svec();

        for (const auto &src : sources) {
            auto p = fs::path(src);
            folders.push_back(src);
        }

        return folders;
    }

    fvec compare_files(const fvec last, const fvec current) {
        const auto logger = get_logger();

        // create a file lookup map
        auto fmap = std::map<std::string, FileSpec>();
        for (const auto &file : last) {
            fmap.emplace(file.filename, file);
        }

        auto changes = fvec();
        for (const auto &file : current) {
            auto search = fmap.find(file.filename);
            if (search != fmap.end()) {
                auto last_file = search->second;
                if (last_file.size != file.size || last_file.last_modified != file.last_modified) {
                    changes.emplace_back(file);
                    logger->info("file change: {}", file.filename);
                }
            } else {
                changes.emplace_back(file);
                logger->info("new file: {}", file.filename);
            }
        }

        return changes;
    }

    void start_scan(replica::config::Config config) {
        const auto logger = get_logger();

        logger->info("Begin scan, Version: {}", replica::APP_VERSION);
        logger->info("Config: {}", config.to_string());

        const auto folders = validate_folders(config.sources);

        auto last_scan = scan_folders(folders, config.extensions, config.excludes);

        for (const auto &file : last_scan) {
            logger->info("{} {} {} {}", file.filename, file.last_modified, file.size, file.last_scan);
        }

        logger->info("total of {} files", last_scan.size());

        std::thread t = replica::ticker::start(config.interval, [&](const size_t tick) -> bool {
            auto current_scan = scan_folders(folders, config.extensions, config.excludes);

            // if there are changes run the cmd then do the last_scan again...
            auto changes = compare_files(last_scan, current_scan);

            if (changes.size() > 0) {
                logger->info("tick: {}, file change count: {}", tick, changes.size());

                // trigger the command...
                last_scan.swap(current_scan);
                logger->flush();
                
                int rcode = std::system(config.cmd.c_str());
                if (!rcode) {
                    logger->warn("system call '{}' filed with code: {}", config.cmd, rcode);
                }
            }

            logger->flush();

            return true;
        });

        t.join();
    }
}

#endif
