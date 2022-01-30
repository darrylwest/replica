#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <cstring>
#include "../include/replica.hpp"

TEST_CASE("construct", "[create]") {
    SECTION("test version") {
        auto const vers = replica::APP_VERSION;
        CHECK(vers != nullptr);
        REQUIRE(strncmp(vers, "22.", 3) == 0);
        REQUIRE_THAT(vers, Catch::Matchers::Contains("22."));
    }
    SECTION("test banner") {
        auto const banner = replica::BANNER;
        CHECK(banner != nullptr);
        REQUIRE(strlen(banner) > 35);
        REQUIRE(strlen(banner) < 128);
        REQUIRE_THAT(banner, Catch::Matchers::Contains("Replica"));
        REQUIRE_THAT(banner, Catch::Matchers::Contains("Service"));
        REQUIRE_THAT(banner, Catch::Matchers::Contains("Rain City Software"));
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
    SECTION("zero args") {
        auto poll_spec = replica::PollSpec{false, 12};
        REQUIRE(poll_spec.enabled == false);
        REQUIRE(poll_spec.interval == 12);
    }
}
