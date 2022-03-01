
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
            bool dryrun = true;
            bool skip = false;
            std::string replica_home = ".replica";
            std::string config_file = "config.json";
            int interval = 1000;
            std::vector<std::string> sources;
            std::string cmd;
        };

        Config parse(int argc, const char* argv[]) {
            Config config;

            config.name = std::string(argv[0]);

            try {
                cxxopts::Options options(config.name, replica::BANNER);

                options.add_options()
                    ("v,version", "Show the current version")
                    ("h,help", "Show this help")
                    ("d,dryrun", "Just parse but don't run replica", cxxopts::value<bool>()->default_value("false"))
                    ("c,config", "The configuration file", cxxopts::value<std::string>())
                    ("i,interval", "Specify the loop inteval in milliseconds", cxxopts::value<int>())
                    ("s,sources", "A delimited list of source folders to watch", cxxopts::value<std::vector<std::string>>())
                    ("cmd", "A system command to run when a watched file is modified", cxxopts::value<std::string>())
                ;

                auto result = options.parse(argc, argv);

                if (result.count("version")) {
                    fmt::print("{} Version: {}\n", config.name, replica::APP_VERSION);
                    config.skip = true;
                }

                if (result.count("help")) {
                    fmt::print("{}\n", options.help());
                    config.skip = true;
                }

                if (result.count("config")) {
                    config.config_file = result["config"].as<std::string>();
                }

                if (result.count("sources")) {
                    config.sources = result["sources"].as<std::vector<std::string>>();
                }

                if (result.count("cmd")) {
                    config.cmd = result["cmd"].as<std::string>();
                }

                if (result.count("interval")) {
                    config.interval = result["interval"].as<int>();
                }
            } catch (const cxxopts::OptionException& e) {
                auto style = fg(fmt::color::red) | fmt::emphasis::bold;
                fmt::print(style, "Error parsing options: {}\n", e.what());
                config.skip = true;
            }

            return config;
        }
    }
}

#endif
