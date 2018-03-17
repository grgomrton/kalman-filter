#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"

using namespace snowhouse;

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE("Factorials are computed") {
    AssertThat(Factorial(1), Is().EqualTo(1));
    AssertThat(Factorial(2), Is().EqualTo(2));
    AssertThat(Factorial(3), Is().EqualTo(6));
    AssertThat(Factorial(10), Is().EqualTo(3628800));
}

TEST_CASE("A failing test case should display an explanation for the failure") {
    AssertThat(1, Is().EqualTo(2));
}