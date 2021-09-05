#include <catch2/catch_test_macros.hpp>

#include <hersh/printer.hpp>

TEST_CASE("Test printer", "[printer]") {
    
    REQUIRE(hersh::print("") == "");
    REQUIRE(hersh::print("something ") == "something ");
}
