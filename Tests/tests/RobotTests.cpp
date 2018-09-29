#include "ILocalizer.h"
#include "IMovingObjectContainer.h"
#include "Robot.h"
#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"
#include "fakeit/standalone/fakeit.hpp"

using namespace snowhouse;
using namespace fakeit;

TEST_CASE("Robot movement accuracy should not be negative") {
    double moveAccuracy = -8.0;

    AssertThrows(std::invalid_argument, Robot(moveAccuracy));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("moveCommandAccuracy"));
}

TEST_CASE("Robot movement accuracy should not be zero") {
    double moveAccuracy = 0.0;

    AssertThrows(std::invalid_argument, Robot(moveAccuracy));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("moveCommandAccuracy"));
}

TEST_CASE("Robot should return the specified move accuracy") {
    double moveAccuracy = 8.0;
    double precision = 0.001;
    Robot robot(moveAccuracy);

    auto storedAccuracy = robot.getMoveCommandAccuracyInPercentage();

    AssertThat(storedAccuracy, Is().EqualToWithDelta(moveAccuracy, precision));
}

TEST_CASE("A listener should be notified about an executed move command") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    int callCount = 0;
    auto listener = std::make_shared<std::function<void(double)>>([&](double distance) { callCount++; });
    robot.addMoveCommandListener(listener);
    int expectedCallCount = 1;
    double distance = 10.0;

    robot.move(distance);

    AssertThat(callCount, Is().EqualTo(expectedCallCount));
}

TEST_CASE("Robot should pass the executed distance to the listener") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    double receivedDistance = 0.0;
    auto listener = std::make_shared<std::function<void(double)>>([&](double distance) { receivedDistance = distance; });
    robot.addMoveCommandListener(listener);
    double distance = 12.55;
    double expectedDistance = 12.55;
    double precision = 0.001;

    robot.move(distance);

    AssertThat(receivedDistance, Is().EqualToWithDelta(expectedDistance, precision));
}

TEST_CASE("Multiple listeners should be notified about an executed move command") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    int callCountInFirstListener = 0;
    int callCountInSecondListener = 0;
    auto firstListener = std::make_shared<std::function<void(double)>>([&](double) { callCountInFirstListener++; });
    auto secondListener = std::make_shared<std::function<void(double)>>([&](double) { callCountInSecondListener++; });
    robot.addMoveCommandListener(firstListener);
    robot.addMoveCommandListener(secondListener);
    int expectedCallCount = 1;
    double distance = 10.0;

    robot.move(distance);

    AssertThat(callCountInFirstListener, Is().EqualTo(expectedCallCount));
    AssertThat(callCountInSecondListener, Is().EqualTo(expectedCallCount));
}

TEST_CASE("Multiple listeners should be notified about consecutive move commands") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    int callCountInFirstListener = 0;
    int callCountInSecondListener = 0;
    auto firstListener = std::make_shared<std::function<void(double)>>([&](double) { callCountInFirstListener++; });
    auto secondListener = std::make_shared<std::function<void(double)>>([&](double) { callCountInSecondListener++; });
    robot.addMoveCommandListener(firstListener);
    robot.addMoveCommandListener(secondListener);
    int expectedCallCount = 2;
    double distance = 10.0;

    robot.move(distance);
    robot.move(-distance);

    AssertThat(callCountInFirstListener, Is().EqualTo(expectedCallCount));
    AssertThat(callCountInSecondListener, Is().EqualTo(expectedCallCount));
}

TEST_CASE("An expired listener should not be called") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    int callCount = 0;
    auto listener = std::make_shared<std::function<void(double)>>([&](double distance) { callCount++; });
    robot.addMoveCommandListener(listener);
    listener.reset();
    int expectedCallCount = 0; // todo assert log - once we have it
    double distance = 10.0;

    robot.move(distance);

    AssertThat(callCount, Is().EqualTo(expectedCallCount));
}

TEST_CASE("A throwing listener should be removed from the listeners") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    int normalListenerCallCount = 0;
    auto properListener = std::make_shared<std::function<void(double)>>([&](double) {
        normalListenerCallCount++;
    });
    int throwingCallCount = 0;
    auto exceptionThrowingListener = std::make_shared<std::function<void(double)>>([&](double) {
        throwingCallCount++;
        throw "Fail for test purposes";
    });
    robot.addMoveCommandListener(properListener);
    robot.addMoveCommandListener(exceptionThrowingListener);
    int expectedNormalListenerCallCount = 2;
    int expectedThrowingListenerCallCount = 1;
    double distance = 10.0;

    robot.move(distance);
    robot.move(distance);

    AssertThat(normalListenerCallCount, Is().EqualTo(expectedNormalListenerCallCount));
    AssertThat(throwingCallCount, Is().EqualTo(expectedThrowingListenerCallCount));
}


TEST_CASE("An exception throwing listener should be removed from the listeners") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    int normalListenerCallCount = 0;
    auto properListener = std::make_shared<std::function<void(double)>>([&](double) {
        normalListenerCallCount++;
    });
    int throwingCallCount = 0;
    auto exceptionThrowingListener = std::make_shared<std::function<void(double)>>([&](double) {
        throwingCallCount++;
        throw std::logic_error("Exception raised for test purposes");
    });
    robot.addMoveCommandListener(properListener);
    robot.addMoveCommandListener(exceptionThrowingListener);
    int expectedNormalListenerCallCount = 2;
    int expectedThrowingListenerCallCount = 1;
    double distance = 10.0;

    robot.move(distance);
    robot.move(distance);

    AssertThat(normalListenerCallCount, Is().EqualTo(expectedNormalListenerCallCount));
    AssertThat(throwingCallCount, Is().EqualTo(expectedThrowingListenerCallCount));
}

TEST_CASE("After an expired listener removed the rest of the listeners should be called") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    int normalListenerCallCount = 0;
    auto properListener = std::make_shared<std::function<void(double)>>([&](double) {
        normalListenerCallCount++;
    });
    int deletedCallCount = 0;
    auto deletedListener = std::make_shared<std::function<void(double)>>([&](double) {
        deletedCallCount ++;
    });
    robot.addMoveCommandListener(deletedListener);
    robot.addMoveCommandListener(properListener);
    int expectedNormalListenerCallCount = 3;
    int expectedDeletedListenerCallCount = 1;
    double distance = 10.0;

    robot.move(distance);
    deletedListener.reset();
    robot.move(distance);
    robot.move(distance);

    AssertThat(normalListenerCallCount, Is().EqualTo(expectedNormalListenerCallCount));
    AssertThat(deletedCallCount , Is().EqualTo(expectedDeletedListenerCallCount));
}