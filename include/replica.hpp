//
// Created by Darryl West on 1/27/22.
//

#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <filesystem>
#include "cxxopts.hpp"

namespace replica {
    const char* APP_VERSION = "22.1.29";
    const char* BANNER = "Replica Backup Service © 2022 Rain City Software";

    struct PollSpec {
        bool enabled {false};
        long interval {60000};
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
    };

    struct Config {
        bool dryrun = true;
        std::string replica_home = ".replica";
        std::string config_file = "config.json";
        PollSpec poll_spec;
    };

    Config parse(int argc, char *argv[]) {
        Config config;
        PollSpec poll_spec;

        try {
            cxxopts::Options options(argv[0], BANNER);

            options.add_options()
                ("v,version", "Show the current version")
                ("h,help", "Show this help")
                ("p,poll", "enable polling", cxxopts::value<bool>()->default_value("false"))
                ("d,dryrun", "Just parse but don't run replica", cxxopts::value<bool>()->default_value("false"))
                ("c,config", "The configuration file", cxxopts::value<std::string>());

            auto result = options.parse(argc, argv);

            if (result.count("version")) {
                std::cout << argv[0] << " Version: " << replica::APP_VERSION << std::endl;
                exit(0);
            }

            if (result.count("help")) {
                std::cout << options.help() << std::endl;
                exit(0);
            }

            if (result.count("poll")) {
                poll_spec.enabled = result["poll"].as<bool>();
            }
        } catch (const cxxopts::OptionException& e) {
            std::cout << "error parsing options: " << e.what() << std::endl;
        }

        config.poll_spec = poll_spec;

        return config;
    }

}

// #endif //REPLICA_REPLICA_HPP
