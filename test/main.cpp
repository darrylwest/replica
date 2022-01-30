#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <cstring>
#include "../include/replica.hpp"

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

    SECTION("poll spec struct - default") {
        auto poll_spec = replica::PollSpec();
        REQUIRE(poll_spec.enabled == false);
        REQUIRE(poll_spec.interval == 60000);
    }

    SECTION("poll spec struct - custom") {
        auto interval = 5000;
        auto poll_spec = replica::PollSpec{true, interval};
        REQUIRE(poll_spec.enabled == true);
        REQUIRE(poll_spec.interval == interval);
    }
}

TEST_CASE("command line", "[parse]") {
    char name[] = "replica";
    char version[] = "--version";
    char help[] = "--help";
    char poll[] = "--poll";
    char config_option[] = "--config";
    char config_file[] = "custom-config.json";

    SECTION("zero args") {
        int argc = 1;
        char *argv[] = {name};
        auto config = replica::parse(argc, argv);
        REQUIRE(std::end(argv) - std::begin(argv) == argc);
        REQUIRE_THAT(config.name, cm::Equals(name));
        REQUIRE_THAT(config.replica_home, cm::Equals(".replica"));
        REQUIRE(config.dryrun == true);
        REQUIRE(config.skip == false);
        REQUIRE(config.poll_spec.enabled == false);
        REQUIRE_THAT(config.config_file, cm::Matches("config.json"));
    }

    SECTION("version") {
        char *argv[] = { name, version};
        int argc = std::end(argv) - std::begin(argv);
        auto config = replica::parse(argc, argv);
        REQUIRE_THAT(config.name, cm::Equals(name));
        REQUIRE_THAT(config.replica_home, cm::Equals(".replica"));
        REQUIRE(config.dryrun == true);
        REQUIRE(config.skip == true);
        REQUIRE(config.poll_spec.enabled == false);
        REQUIRE_THAT(config.config_file, cm::Matches("config.json"));
    }

    SECTION("help") {
        char *argv[] = { name, help};
        int argc = std::end(argv) - std::begin(argv);
        auto config = replica::parse(argc, argv);
        REQUIRE_THAT(config.name, cm::Equals(name));
        REQUIRE_THAT(config.replica_home, cm::Equals(".replica"));
        REQUIRE(config.dryrun == true);
        REQUIRE(config.skip == true);
        REQUIRE(config.poll_spec.enabled == false);
        REQUIRE_THAT(config.config_file, cm::Matches("config.json"));
    }

    SECTION("poll") {
        char *argv[] = { name, poll};
        int argc = std::end(argv) - std::begin(argv);
        auto config = replica::parse(argc, argv);
        REQUIRE_THAT(config.name, cm::Equals(name));
        REQUIRE_THAT(config.replica_home, cm::Equals(".replica"));
        REQUIRE(config.dryrun == true);
        REQUIRE(config.skip == false);
        REQUIRE(config.poll_spec.enabled == true);
        REQUIRE_THAT(config.config_file, cm::Matches("config.json"));
    }

    SECTION("config") {
        char *argv[] = { name, config_option, config_file};
        int argc = std::end(argv) - std::begin(argv);
        auto config = replica::parse(argc, argv);
        REQUIRE_THAT(config.name, cm::Equals(name));
        REQUIRE_THAT(config.replica_home, cm::Equals(".replica"));
        REQUIRE(config.dryrun == true);
        REQUIRE(config.skip == false);
        REQUIRE(config.poll_spec.enabled == true);
        REQUIRE_THAT(config.config_file, cm::Matches("custom-config.json"));
    }
}
