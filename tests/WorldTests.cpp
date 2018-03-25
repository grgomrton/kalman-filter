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
    Mock<IMovingObject> robot;
    double accuracy = 10.0;
    When(Method(robot, getMoveCommandAccuracyInPercentage)).AlwaysReturn(accuracy);
    World world(initialRobotPosition);

    world.moveCommandExecuted(robot.get(), moveDistance);
    auto currentPosition = world.getRealRobotPosition();

    AssertThat(currentPosition, Is().GreaterThan(initialRobotPosition));
}

TEST_CASE("World should add a gaussian noise to the executed move commands", "[random-test]") {
    // Tested with a one-way table chi square test
    std::vector<double> values;
    int sampleSize = 100;
    double higherBoundToKeepNullHypothesis = 7.81473;
    double expectedItemCountInOneStandardDeviationBelowMean = sampleSize * 0.341;
    double expectedItemCountInOneStandardDeviationAboveMean = sampleSize * 0.341;
    double expectedItemCountBelowOneStandardDeviationFromMean = sampleSize * 0.159;
    double expectedItemCountAboveOneStandardDeviationFromMean = sampleSize * 0.159;
    double initialRobotPose = 0.0;
    double distance = 1.0;
    double accuracy = 10.0;
    double standardDeviation = 0.05;
    auto itemIsBelowOneStandardDeviationBelowMean = [distance, standardDeviation](double item){ return item < distance - standardDeviation; };
    auto itemIsInOneStandardDeviationBelowMean = [distance, standardDeviation](double item){ return (item >= distance - standardDeviation) && (item < distance); };
    auto itemIsInOneStandardDeviationAboveMean = [distance, standardDeviation](double item){ return (item >= distance) && (item < distance + standardDeviation); };
    auto itemIsAboveOneStandardDeviationAboveMean = [distance, standardDeviation](double item){ return item >= distance + standardDeviation; };
    Mock<IMovingObject> robot;
    When(Method(robot, getMoveCommandAccuracyInPercentage)).AlwaysReturn(accuracy);
    IMovingObject& robotInstance = robot.get();

    for (int i=0; i<sampleSize; i++) {
        World world(initialRobotPose);
        world.moveCommandExecuted(robotInstance, distance);
        values.push_back(world.getRealRobotPosition());
    }

    auto itemCountBelowOneStandardDeviationBelowMean = std::count_if(values.begin(), values.end(), itemIsBelowOneStandardDeviationBelowMean);
    auto itemCountInOneStandardDeviationBelowMean = std::count_if(values.begin(), values.end(), itemIsInOneStandardDeviationBelowMean);
    auto itemCountInOneStandardDeviationAboveMean = std::count_if(values.begin(), values.end(), itemIsInOneStandardDeviationAboveMean);
    auto itemCountAboveOneStandardDeviationAboveMean = std::count_if(values.begin(), values.end(), itemIsAboveOneStandardDeviationAboveMean);
    auto calculateChiSquare = [](double measured, double expected) { return pow(measured - expected, 2.0) / expected; };
    double chiSquare = 0.0;
    chiSquare += calculateChiSquare(itemCountBelowOneStandardDeviationBelowMean, expectedItemCountBelowOneStandardDeviationFromMean);
    chiSquare += calculateChiSquare(itemCountInOneStandardDeviationBelowMean, expectedItemCountInOneStandardDeviationBelowMean);
    chiSquare += calculateChiSquare(itemCountInOneStandardDeviationAboveMean, expectedItemCountInOneStandardDeviationAboveMean);
    chiSquare += calculateChiSquare(itemCountAboveOneStandardDeviationAboveMean, expectedItemCountAboveOneStandardDeviationFromMean);
    AssertThat(chiSquare, Is().LessThan(higherBoundToKeepNullHypothesis));
}