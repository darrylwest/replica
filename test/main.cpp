#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <cstring>
#include "../include/replica.hpp"

TEST_CASE("construct", "[create]") {
    SECTION("test version") {
        auto const vers = replica::APP_VERSION;
        REQUIRE(vers != nullptr);
        REQUIRE(strcmp(vers, "22.1.29") == 0);
    }
    SECTION("test banner") {
        auto const banner = replica::BANNER;
        REQUIRE(banner != nullptr);
        REQUIRE(strlen(banner) > 10);
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
