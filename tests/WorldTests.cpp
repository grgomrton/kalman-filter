#include <IGaussianNoiseProvider.h>
#include <GaussianNoiseProvider.h>
#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"
#include "fakeit/standalone/fakeit.hpp"
#include "World.h"

using namespace snowhouse;
using namespace fakeit;

TEST_CASE("After init world should return the initial robot position") {
    double initialRobotPosition = 0;
    double precision = 0.001;
    Mock<IGaussianNoiseProvider> noiseGenerator;
    World world(initialRobotPosition, noiseGenerator.get());

    auto currentPosition = world.getRealRobotPosition();

    AssertThat(currentPosition, Is().EqualToWithDelta(initialRobotPosition, precision));
}

TEST_CASE("After a move command has executed perfectly the robot's position should be exactly at the destination") {
    double initialRobotPosition = -0.5;
    double moveDistance = 1.3;
    double moveAccuracy = 10.0;
    double noise = 0.0;
    double expectedPosition = 0.8;
    double precision = 0.001;
    Mock<IMovingObject> robot;
    When(Method(robot, getMoveCommandAccuracyInPercentage)).AlwaysReturn(moveAccuracy);
    Mock<IGaussianNoiseProvider> noiseGenerator;
    When(Method(noiseGenerator, getNoise)).AlwaysReturn(noise);
    World world(initialRobotPosition, noiseGenerator.get());

    world.moveCommandExecuted(robot.get(), moveDistance);
    auto currentPosition = world.getRealRobotPosition();

    AssertThat(currentPosition, Is().EqualToWithDelta(expectedPosition, precision));
}

TEST_CASE("During executing the move command noise should be added") {
    double initialRobotPosition = -0.5;
    double moveDistance = 1.3;
    double moveAccuracy = 10.0;
    double noise = -0.1;
    double expectedPosition = 0.7;
    double precision = 0.001;
    Mock<IMovingObject> robot;
    When(Method(robot, getMoveCommandAccuracyInPercentage)).AlwaysReturn(moveAccuracy);
    Mock<IGaussianNoiseProvider> noiseGenerator;
    When(Method(noiseGenerator, getNoise)).AlwaysReturn(noise);
    World world(initialRobotPosition, noiseGenerator.get());

    world.moveCommandExecuted(robot.get(), moveDistance);
    auto currentPosition = world.getRealRobotPosition();

    AssertThat(currentPosition, Is().EqualToWithDelta(expectedPosition, precision));
}
