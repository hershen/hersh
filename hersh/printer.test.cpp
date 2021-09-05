#include <hersh/printer.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test printer", "[printer]") {
    
    REQUIRE(hersh::print("") == "");
    REQUIRE(hersh::print("something ") == "something ");
}
