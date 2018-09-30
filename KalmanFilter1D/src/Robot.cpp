#include <stdexcept>
#include <algorithm>
#include <exception>
#include "Robot.h"

Robot::Robot(double moveCommandAccuracyInPercentage) :
        moveCommandAccuracyInPercentage(moveCommandAccuracyInPercentage),
        listeners() {
    if (moveCommandAccuracyInPercentage <= 0.0) {
        throw std::invalid_argument("moveCommandAccuracyInPercentage must be a non-zero positive value");
    }
}

void Robot::move(double distanceInMetres) {
    for (auto& listener : listeners) {
        if (auto callableListener = listener.lock()) {
            callableListener->onRobotMoveCommandReceived(distanceInMetres);
        }
    }
    auto isExpired = [](const std::weak_ptr<IRobotObserver>& listener) { return listener.expired(); };
    listeners.erase(std::remove_if(begin(listeners), end(listeners), isExpired), end(listeners));
}

double Robot::getMoveCommandAccuracyInPercentage() const {
    return moveCommandAccuracyInPercentage;
}

void Robot::addMoveCommandListener(const std::shared_ptr<IRobotObserver>& listener) {
    listeners.push_back(listener); // todo disable multiple subscription
}
