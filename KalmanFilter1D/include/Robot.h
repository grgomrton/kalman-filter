#pragma once

#include <functional>
#include <vector>
#include <memory>
#include "IObservableRobot.h"
#include "IRobotObserver.h"

class Robot : public IObservableRobot {
public:
    explicit Robot(double moveCommandAccuracyInPercentage);

    void move(double distanceInMetres);

    double getMoveCommandAccuracyInPercentage() const override;

    void addMoveCommandListener(const std::shared_ptr<IRobotObserver>& listener);

private:
    double moveCommandAccuracyInPercentage;
    std::vector<std::weak_ptr<IRobotObserver>> listeners;

};
