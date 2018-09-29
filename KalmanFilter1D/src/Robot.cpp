#include <stdexcept>
#include <iostream>
#include <exception>
#include <algorithm>
#include "Robot.h"

Robot::Robot(double moveCommandAccuracyInPercentage) :
        moveCommandAccuracyInPercentage(moveCommandAccuracyInPercentage),
        listeners() {
    if (moveCommandAccuracyInPercentage <= 0.0) {
        throw std::invalid_argument("moveCommandAccuracyInPercentage must be a non-zero positive value");
    }
}

void Robot::move(double distanceInMetres) {
    std::vector<std::weak_ptr<std::function<void(double)>>> brokenListeners;

    for (auto& listener : listeners) {
        if (auto callable = listener.lock()) {
            try {
                (*callable)(distanceInMetres);
            }
            catch (std::exception& e) {
                brokenListeners.push_back(listener); // todo log
            }
            catch (...) {
                brokenListeners.push_back(listener); // todo log
            }
        } else {
            brokenListeners.push_back(listener); // todo log
        }
    }

    auto isBroken = [&](std::weak_ptr<std::function<void(double)>>& listener) {
        for (auto& brokenListener : brokenListeners) {
            if (pointsToSameObject(listener, brokenListener)) {
                return true;
            }
        }
        return false;
    };
    listeners.erase(remove_if(begin(listeners), end(listeners), isBroken), end(listeners));
}

double Robot::getMoveCommandAccuracyInPercentage() {
    return moveCommandAccuracyInPercentage;
}

void Robot::addMoveCommandListener(const std::shared_ptr<std::function<void(double)>>& listener) {
    listeners.push_back(listener); // todo disable multiple subscription
}

template<typename T>
bool Robot::pointsToSameObject(const std::weak_ptr<T>& item, const std::weak_ptr<T>& itemToCompareWith) {
    return !(item.owner_before(itemToCompareWith) || itemToCompareWith.owner_before(item));
}
