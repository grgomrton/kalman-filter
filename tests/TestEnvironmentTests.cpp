#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"

using namespace snowhouse;

TEST_CASE("A failing test case should display an explanation for the failure", "[ignore]") {
    AssertThat(1, Is().EqualTo(2));
}

TEST_CASE("Snowhouse can evaluate a complex expression while evaluating collections", "[ignore]") {
    std::vector<int> values;

    values.push_back(1);
    values.push_back(3);

    AssertThat(values, Has().Exactly(1).GreaterThan(2).And().LessThan(4));
    //AssertThat(values, Has().Exactly(1).GreaterThan(4).And().LessThan(5)); // should fail
}