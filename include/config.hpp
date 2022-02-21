
//
// Created by Darryl West on 2022-02-21 13:06:59
//

#pragma once
#ifndef REPLICA_CONFIG_HPP
#define REPLICA_CONFIG_HPP

#include <iostream>
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
}

#endif
