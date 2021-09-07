#include <evaluate.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test evaluate", "[evaluate]") {
    
    REQUIRE(hersh::evaluate("") == "");
    REQUIRE(hersh::evaluate("something ") == "something ");
}
