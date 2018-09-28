#pragma once

#include <functional>
#include <vector>
#include "IMovingObject.h"

class Robot : public IMovingObject {
public:
    explicit Robot(double moveCommandAccuracyInPercentage);
    void move(double distanceInMetres);
    double getMoveCommandAccuracyInPercentage() override;
    void addRobotMoveCommandReceivedListener(std::function<void(double)>); // TODO change it to an interface
private:
    double moveCommandAccuracyInPercentage;
    std::vector<std::function<void(double)>> listeners;
};
