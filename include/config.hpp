
//
// Created by Darryl West on 2022-02-21 13:06:59
//

#pragma once
#ifndef REPLICA_CONFIG_HPP
#define REPLICA_CONFIG_HPP

#include <string>
#include <chrono>
#include <filesystem>
#include "cxxopts.hpp"

namespace replica {
    namespace config {
        struct Config {
            std::string name;
            std::string logger_name = "replica_logger";
            std::string log_filename = "replica.log";
            int max_log_size = 100000;
            int max_log_files = 3;
            bool dryrun = true;
            bool skip = false;
            std::string replica_home = ".replica";
            std::string config_file = "config.json";
            replica::PollSpec poll_spec;
        };

        Config parse(int argc, const char* argv[]) {
            Config config;
            replica::PollSpec poll_spec;

            config.name = std::string(argv[0]);

            try {
                cxxopts::Options options(config.name, replica::BANNER);

                options.add_options()
                    ("v,version", "Show the current version")
                    ("h,help", "Show this help")
                    ("p,poll", "enable polling", cxxopts::value<bool>()->default_value("false"))
                    ("d,dryrun", "Just parse but don't run replica", cxxopts::value<bool>()->default_value("false"))
                    ("c,config", "The configuration file", cxxopts::value<std::string>());

                auto result = options.parse(argc, argv);

                if (result.count("version")) {
                    fmt::print("{} Version: {}\n", config.name, replica::APP_VERSION);
                    config.skip = true;
                }

                if (result.count("help")) {
                    fmt::print("{}\n", options.help());
                    config.skip = true;
                }

                if (result.count("poll")) {
                    poll_spec.enabled = result["poll"].as<bool>();
                }

                if (result.count("config")) {
                    config.config_file = result["config"].as<std::string>();
                }
            } catch (const cxxopts::OptionException& e) {
                auto style = fg(fmt::color::red) | fmt::emphasis::bold;
                fmt::print(style, "Error parsing options: {}\n", e.what());
                config.skip = true;
            }

            config.poll_spec = poll_spec;

            return config;
        }
    }
}

#endif
