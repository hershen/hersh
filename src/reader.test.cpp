#include <reader.hpp>

#include <iostream>
#include <ostream>
#include <sstream>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test Reader", "[Reader]") {
    std::istringstream istringstream("alon");
    std::ostringstream ostringstream;

    hersh::Reader reader(istringstream, ostringstream);

    SECTION("Test with default prompt") {
      REQUIRE(reader.read() == "alon");
      REQUIRE(ostringstream.str() == reader.getPrompt());
    }
    
    SECTION("Test with non-default prompt") {
      reader.setPrompt("bestPrompt ");
      REQUIRE(reader.getPrompt() == "bestPrompt ");

      REQUIRE(reader.read() == "alon");
      REQUIRE(ostringstream.str() == "bestPrompt ");
    }
}
