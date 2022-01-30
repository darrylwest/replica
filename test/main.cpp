#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <string>
#include "../include/replica.hpp"

TEST_CASE("construct", "[create]") {
  SECTION("test version") {
    auto const vers = replica::APP_VERSION;
    REQUIRE(vers != nullptr);
  }
}
