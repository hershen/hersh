#include <catch2/catch_test_macros.hpp>

#include <hersh/reader.hpp>

#include <iostream>
#include <ostream>
#include <sstream>

TEST_CASE("Test Reader", "[Reader]") {
    std::istringstream istringstream("alon");
    std::ostringstream ostringstream;

    hersh::Reader reader(istringstream, ostringstream);

    REQUIRE(reader.getPrompt() == "");

    SECTION("Test with default prompt") {
      REQUIRE(reader.read() == "alon");
      REQUIRE(ostringstream.str() == "");
    }
    
    SECTION("Test with non-default prompt") {
      reader.setPrompt("bestPrompt ");
      REQUIRE(reader.getPrompt() == "bestPrompt ");

      REQUIRE(reader.read() == "alon");
      REQUIRE(ostringstream.str() == "bestPrompt ");
    }
}
