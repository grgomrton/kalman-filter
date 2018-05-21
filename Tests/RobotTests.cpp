#include <ILocalizer.h>
#include <IMovingObjectPositionStore.h>
#include <Robot.h>
#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"
#include "fakeit/standalone/fakeit.hpp"

using namespace snowhouse;
using namespace fakeit;

TEST_CASE("Robot should notify localizer about an executed move command") {
    Mock<ILocalizer> localizer;
    When(Method(localizer, moveCommandExecuted)).AlwaysReturn();
    Mock<IMovingObjectPositionStore> world;
    When(Method(world, moveCommandExecuted)).AlwaysReturn();
    double moveAccuracy = 10.0;
    Robot robot(moveAccuracy, localizer.get(), world.get());
    double distanceInMetres = 10.0;

    robot.move(distanceInMetres);

    Verify(Method(localizer, moveCommandExecuted)).Exactly(1);
}

TEST_CASE("Robot should notify world about an executed move command") {
    Mock<ILocalizer> localizer;
    When(Method(localizer, moveCommandExecuted)).AlwaysReturn();
    Mock<IMovingObjectPositionStore> world;
    When(Method(world, moveCommandExecuted)).AlwaysReturn();
    double moveAccuracy = 10.0;
    double precision = 0.001;
    Robot robot(moveAccuracy, localizer.get(), world.get());
    double distanceInMetres = 10.0;

    robot.move(distanceInMetres);

    auto passedAccuracyMatchesSpecifiedOne = [moveAccuracy, precision]
            (IMovingObject& robot, double distance) { return std::abs(robot.getMoveCommandAccuracyInPercentage() - moveAccuracy) < precision; };
    Verify(Method(world, moveCommandExecuted)).Exactly(1);
    Verify(Method(world, moveCommandExecuted).Matching(passedAccuracyMatchesSpecifiedOne)).Exactly(1);
}

TEST_CASE("Robot movement accuracy should not be negative") {
    Mock<ILocalizer> localizer;
    Mock<IMovingObjectPositionStore> world;
    double moveAccuracy = -8.0;

    AssertThrows(std::invalid_argument, Robot(moveAccuracy, localizer.get(), world.get()));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("moveCommandAccuracy"));
}

TEST_CASE("Robot movement accuracy should not be zero") {
    Mock<ILocalizer> localizer;
    Mock<IMovingObjectPositionStore> world;
    double moveAccuracy = 0.0;

    AssertThrows(std::invalid_argument, Robot(moveAccuracy, localizer.get(), world.get()));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("moveCommandAccuracy"));
}

TEST_CASE("Robot should return the specified move accuracy") {
    Mock<ILocalizer> localizer;
    Mock<IMovingObjectPositionStore> world;
    double moveAccuracy = 8.0;
    double precision = 0.001;
    Robot robot(moveAccuracy, localizer.get(), world.get());

    auto storedAccuracy = robot.getMoveCommandAccuracyInPercentage();

    AssertThat(storedAccuracy, Is().EqualToWithDelta(moveAccuracy, precision));
}