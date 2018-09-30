#include "ILocalizer.h"
#include "IRobotObserver.h"
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
    Mock<IRobotObserver> listenerMock;
    Fake(Dtor(listenerMock));
    When(Method(listenerMock, onRobotMoveCommandReceived)).AlwaysDo([&](double distance) { callCount++; });
    std::shared_ptr<IRobotObserver> sharedListener(&listenerMock.get());
    robot.addMoveCommandListener(sharedListener);
    int expectedCallCount = 1;
    double distance = 10.0;

    robot.move(distance);

    AssertThat(callCount, Is().EqualTo(expectedCallCount));
}

TEST_CASE("Robot should pass the executed distance to the listener") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    double receivedDistance = 0.0;
    Mock<IRobotObserver> listenerMock;
    Fake(Dtor(listenerMock));
    When(Method(listenerMock, onRobotMoveCommandReceived)).AlwaysDo([&](double distance) { receivedDistance = distance; });
    std::shared_ptr<IRobotObserver> sharedListener(&listenerMock.get());
    robot.addMoveCommandListener(sharedListener);
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
    Mock<IRobotObserver> firstListenerMock;
    Mock<IRobotObserver> secondListenerMock;
    Fake(Dtor(firstListenerMock));
    Fake(Dtor(secondListenerMock));
    When(Method(firstListenerMock, onRobotMoveCommandReceived)).AlwaysDo([&](double) { callCountInFirstListener++; });
    When(Method(secondListenerMock, onRobotMoveCommandReceived)).AlwaysDo([&](double) { callCountInSecondListener++; });
    std::shared_ptr<IRobotObserver> sharedFirstListener(&firstListenerMock.get());
    std::shared_ptr<IRobotObserver> sharedSecondListener(&secondListenerMock.get());
    robot.addMoveCommandListener(sharedFirstListener);
    robot.addMoveCommandListener(sharedSecondListener);
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
    Mock<IRobotObserver> firstListenerMock;
    Mock<IRobotObserver> secondListenerMock;
    Fake(Dtor(firstListenerMock));
    Fake(Dtor(secondListenerMock));
    When(Method(firstListenerMock, onRobotMoveCommandReceived)).AlwaysDo([&](double) { callCountInFirstListener++; });
    When(Method(secondListenerMock, onRobotMoveCommandReceived)).AlwaysDo([&](double) { callCountInSecondListener++; });
    std::shared_ptr<IRobotObserver> sharedFirstListener(&firstListenerMock.get());
    std::shared_ptr<IRobotObserver> sharedSecondListener(&secondListenerMock.get());
    robot.addMoveCommandListener(sharedFirstListener);
    robot.addMoveCommandListener(sharedSecondListener);
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
    Mock<IRobotObserver> listenerMock;
    Fake(Dtor(listenerMock));
    When(Method(listenerMock, onRobotMoveCommandReceived)).AlwaysDo([&](double distance) { callCount++; });
    std::shared_ptr<IRobotObserver> sharedListener(&listenerMock.get());
    robot.addMoveCommandListener(sharedListener);
    int expectedCallCount = 0;
    double distance = 10.0;

    sharedListener.reset();
    robot.move(distance);

    AssertThat(callCount, Is().EqualTo(expectedCallCount));
}

TEST_CASE("After an expired listener removed the rest of the listeners should be called") {
    double moveAccuracy = 8.0;
    Robot robot(moveAccuracy);
    int aliveListenerCallCount = 0;
    int deletedListenerCallCount = 0;
    Mock<IRobotObserver> aliveListenerMock;
    Mock<IRobotObserver> deletedListenerMock;
    Fake(Dtor(aliveListenerMock));
    Fake(Dtor(deletedListenerMock));
    When(Method(aliveListenerMock, onRobotMoveCommandReceived)).AlwaysDo([&](double) { aliveListenerCallCount++; });
    When(Method(deletedListenerMock, onRobotMoveCommandReceived)).AlwaysDo([&](double) { deletedListenerCallCount++; });
    std::shared_ptr<IRobotObserver> sharedAliveListener(&aliveListenerMock.get());
    std::shared_ptr<IRobotObserver> sharedDeletedListener(&deletedListenerMock.get());
    robot.addMoveCommandListener(sharedAliveListener);
    robot.addMoveCommandListener(sharedDeletedListener);
    int expectedAliveListenerCallCount = 3;
    int expectedDeletedListenerCallCount = 1;
    double distance = 10.0;

    robot.move(distance);
    sharedDeletedListener.reset();
    robot.move(distance);
    robot.move(distance);

    AssertThat(aliveListenerCallCount, Is().EqualTo(expectedAliveListenerCallCount));
    AssertThat(deletedListenerCallCount , Is().EqualTo(expectedDeletedListenerCallCount));
}