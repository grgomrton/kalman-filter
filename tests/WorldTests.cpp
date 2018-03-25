#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"
#include "fakeit/standalone/fakeit.hpp"
#include "World.h"

using namespace snowhouse;
using namespace fakeit;

TEST_CASE("After init world should return the initial robot position") {
    double initialRobotPosition = 0;
    double precision = 0.001;
    World world(initialRobotPosition);

    auto currentPosition = world.getRealRobotPosition();

    AssertThat(currentPosition, Is().EqualToWithDelta(initialRobotPosition, precision));
}

TEST_CASE("After a move command has executed the robot's position should change") {
    double initialRobotPosition = -0.5;
    double moveDistance = 1.3;
    double expectedPosition = 0.8;
    double precision = 0.001;
    World world(initialRobotPosition);

    world.moveCommandExecuted(Mock<IMovingObject>().get(), moveDistance);
    auto currentPosition = world.getRealRobotPosition();

    AssertThat(currentPosition, Is().EqualToWithDelta(expectedPosition, precision));
}