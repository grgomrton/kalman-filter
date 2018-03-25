#include "catch2/catch.hpp"
#include "fakeit/standalone/fakeit.hpp"
#include "snowhouse/snowhouse.h"

using namespace fakeit;
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

struct SomeInterface {
    virtual int foo(int) = 0;
};

TEST_CASE("FakeIt should be able to mock an interface and verify calls to it", "[ignore]") {
    Mock<SomeInterface> mock;
    When(Method(mock, foo)).AlwaysReturn(1);
    int someIrrelevantParameter = 10;

    SomeInterface& i = mock.get();
    auto fooValue = i.foo(someIrrelevantParameter);

    Verify(Method(mock, foo)).Exactly(1);
    //Verify(Method(mock, foo)).Exactly(2); // should display failure reason
    AssertThat(fooValue, Is().EqualTo(1));
}