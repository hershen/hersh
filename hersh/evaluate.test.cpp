#include <catch2/catch_test_macros.hpp>

#include <hersh/evaluate.hpp>

TEST_CASE("Test evaluate", "[evaluate]") {
    
    REQUIRE(hersh::evaluate("") == "");
    REQUIRE(hersh::evaluate("something ") == "something ");
}
