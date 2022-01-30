//
// Created by Darryl West on 1/27/22.
//

#pragma once
#ifndef REPLICA_HPP
#define REPLICA_HPP

#include <iostream>
#include <string>
#include <chrono>
#include <filesystem>
#include "cxxopts.hpp"

namespace replica {
    const char* APP_VERSION = "22.1.30";
    const char* BANNER = "Replica File Exchange Service © 2022 Rain City Software";

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
        std::string name;
        bool dryrun = true;
        bool skip = false;
        std::string replica_home = ".replica";
        std::string config_file = "config.json";
        PollSpec poll_spec;
    };

    Config parse(int argc, char* argv[]) {
        Config config;
        PollSpec poll_spec;

        config.name = std::string(argv[0]);

        try {
            cxxopts::Options options(config.name, BANNER);

            options.add_options()
                ("v,version", "Show the current version")
                ("h,help", "Show this help")
                ("p,poll", "enable polling", cxxopts::value<bool>()->default_value("false"))
                ("d,dryrun", "Just parse but don't run replica", cxxopts::value<bool>()->default_value("false"))
                ("c,config", "The configuration file", cxxopts::value<std::string>());

            auto result = options.parse(argc, argv);

            if (result.count("version")) {
                std::cout << config.name << " Version: " << replica::APP_VERSION << std::endl;
                config.skip = true;
            }

            if (result.count("help")) {
                std::cout << options.help() << std::endl;
                config.skip = true;
            }

            if (result.count("poll")) {
                poll_spec.enabled = result["poll"].as<bool>();
            }

            if (result.count("config")) {
                config.config_file = result["config"].as<std::string>();
            }
        } catch (const cxxopts::OptionException& e) {
            std::cout << "error parsing options: " << e.what() << std::endl;
            config.skip = true;
        }

        config.poll_spec = poll_spec;

        return config;
    }
}

#endif