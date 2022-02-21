//
// Created by Darryl West on 1/27/22.
//

#pragma once
#ifndef REPLICA_HPP
#define REPLICA_HPP

#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "fmt/color.h"

#include <string>
#include <chrono>
#include <vector>
#include <filesystem>

namespace replica {
    const char* APP_VERSION = "22.2.21";
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
        std::string sha;
        std::uintmax_t size;
        fs::file_time_type last_modified;
        tp last_replica;
        tp last_scan;
    };
}

#endif