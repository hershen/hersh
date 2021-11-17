#include "evaluate.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test evaluate", "[evaluate]") {
    
  SECTION("Empty input") {
    REQUIRE(hersh::evaluate("") == "");
  }
  SECTION("Non-empty input") {
    REQUIRE(hersh::evaluate("something ") == "something ");
  }
}
