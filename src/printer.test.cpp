#include <printer.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test printer", "[printer]") {
    
  SECTION("Empty input") {
    REQUIRE(hersh::print("") == "");
  }
  SECTION("Non-empty input") {
    REQUIRE(hersh::print("something ") == "something ");
  }
}
