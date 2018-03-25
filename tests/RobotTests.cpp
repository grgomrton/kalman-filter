#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"
#include "fakeit/standalone/fakeit.hpp"
#include "Robot.h"

using namespace snowhouse;
using namespace fakeit;

TEST_CASE("Robot should notify localizer about an executed move command") {
    Mock<ILocalizer> localizer;
    When(Method(localizer, moveCommandExecuted)).AlwaysReturn();
    Mock<IRobotPositionMaintainer> world;
    When(Method(world, moveCommandExecuted)).AlwaysReturn();
    Robot robot(localizer.get(), world.get());
    double distanceInMetres = 10.0;

    robot.move(distanceInMetres);

    Verify(Method(localizer, moveCommandExecuted)).Exactly(1);
}

TEST_CASE("Robot should notify world about an executed move command") {
    Mock<ILocalizer> localizer;
    When(Method(localizer, moveCommandExecuted)).AlwaysReturn();
    Mock<IRobotPositionMaintainer> world;
    When(Method(world, moveCommandExecuted)).AlwaysReturn();
    Robot robot(localizer.get(), world.get());
    double distanceInMetres = 10.0;

    robot.move(distanceInMetres);

    Verify(Method(world, moveCommandExecuted)).Exactly(1);
}