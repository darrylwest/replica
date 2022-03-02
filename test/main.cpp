#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include "../include/replica.hpp"
#include "../include/config.hpp"

namespace cm = Catch::Matchers;

TEST_CASE("construct", "[create]") {
    SECTION("test version") {
        auto const version = replica::APP_VERSION;
        CHECK(version != nullptr);
        REQUIRE(strncmp(version, "22.", 3) == 0);
        REQUIRE_THAT(version, cm::Contains("22."));
    }

    SECTION("test banner") {
        auto const banner = replica::BANNER;
        CHECK(banner != nullptr);
        REQUIRE(strlen(banner) > 35);
        REQUIRE(strlen(banner) < 128);
        REQUIRE_THAT(banner, cm::Contains("Replica"));
        REQUIRE_THAT(banner, cm::Contains("Service"));
        REQUIRE_THAT(banner, cm::Contains("Rain City Software"));
    }
}

TEST_CASE("command line", "[parse]") {
    char name[] = "replica";
    char version[] = "--version";
    char help[] = "--help";
    char config_option[] = "--config";
    char config_file[] = "test/data/config.json";

    SECTION("zero args") {
        int argc = 1;
        const char *argv[] = {name};
        auto config = replica::config::parse(argc, argv);
        REQUIRE(std::end(argv) - std::begin(argv) == argc);
        REQUIRE_THAT(config.name, cm::Equals(name));
        REQUIRE_THAT(config.replica_home, cm::Equals(".replica"));
        REQUIRE(config.dryrun == false);
        REQUIRE(config.skip == false);
        REQUIRE_THAT(config.config_file, cm::Matches(""));
    }

    SECTION("version") {
        const char *argv[] = { name, version};
        int argc = std::end(argv) - std::begin(argv);
        auto config = replica::config::parse(argc, argv);
        REQUIRE_THAT(config.name, cm::Equals(name));
        REQUIRE_THAT(config.replica_home, cm::Equals(".replica"));
        REQUIRE(config.dryrun == false);
        REQUIRE(config.skip == true);
        REQUIRE_THAT(config.config_file, cm::Matches(""));
    }

    SECTION("help") {
        const char *argv[] = { name, help};
        int argc = std::end(argv) - std::begin(argv);
        auto config = replica::config::parse(argc, argv);
        REQUIRE_THAT(config.name, cm::Equals(name));
        REQUIRE_THAT(config.replica_home, cm::Equals(".replica"));
        REQUIRE(config.dryrun == false);
        REQUIRE(config.skip == true);
        REQUIRE_THAT(config.config_file, cm::Matches(""));
    }

    SECTION("config") {
        const char *argv[] = { name, config_option, config_file};
        int argc = std::end(argv) - std::begin(argv);
        auto config = replica::config::parse(argc, argv);
        REQUIRE_THAT(config.name, cm::Equals(name));
        REQUIRE_THAT(config.replica_home, cm::Equals(".replica"));
        REQUIRE(config.dryrun == false);
        REQUIRE(config.skip == false);
        REQUIRE_THAT(config.config_file, cm::Matches("test/data/config.json"));
    }
}

TEST_CASE("parse config", "[parse_config]") {
    char config_file[] = "test/data/config.json";

    SECTION("parse_json") {
        // first, create the config struct
        const char *argv[] = { "x", "--config", config_file};
        int argc = std::end(argv) - std::begin(argv);
        auto config = replica::config::parse(argc, argv);
        REQUIRE_THAT(config.config_file, cm::Matches("test/data/config.json"));

        replica::config::parse_json(config);
        REQUIRE(config.interval == 900);
    }
}

TEST_CASE("utils", "[utils]") {
    SECTION("read_file") {
        std::string text = utils::read_file("test/data/config.json");

        REQUIRE(text != "");
        REQUIRE(text.size() > 190);
        std::cout << "Text: " << text << '\n';
    }

    SECTION("epoch_now") {
        auto t = utils::epoch_now();
        REQUIRE(t > 1);
    }

    SECTION("file_mod_time") {
        // point to a known file
        auto file = std::filesystem::path{"test/data/config.json"};
        auto ftime = utils::file_mod_time(file);
        auto now = utils::epoch_now();
        REQUIRE(ftime < now);
    }
}