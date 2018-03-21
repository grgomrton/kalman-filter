#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"
#include "../src/UniformSeed.h" // TODO add include library (?)

using namespace snowhouse;

TEST_CASE("The value provided by the seed should be between 0 and 1 (inclusive)") {
    UniformSeed seed;

    double value = seed.getNext();

    AssertThat(value, Is().GreaterThanOrEqualTo(0.0));
    AssertThat(value, Is().LessThanOrEqualTo(1.0));
}

TEST_CASE("Two consecutive values acquired should differ") {
    UniformSeed seed;

    auto firstValue = seed.getNext();
    auto nextValue = seed.getNext();

    AssertThat(nextValue, Is().GreaterThan(firstValue).Or().LessThan(firstValue));
}

TEST_CASE("The distribution of the random values is uniform", "[sporadic]") {
    UniformSeed seed;
    std::vector<double> values;

    values.push_back(seed.getNext());
    values.push_back(seed.getNext());
    values.push_back(seed.getNext());
    values.push_back(seed.getNext());

    AssertThat(values, Has().Exactly(1).GreaterThanOrEqualTo(0.0).And().LessThan(0.25));
    AssertThat(values, Has().Exactly(1).GreaterThanOrEqualTo(0.25).And().LessThan(0.5));
    AssertThat(values, Has().Exactly(1).GreaterThanOrEqualTo(0.5).And().LessThan(0.75));
    AssertThat(values, Has().Exactly(1).GreaterThanOrEqualTo(0.75).And().LessThan(1.0));
}