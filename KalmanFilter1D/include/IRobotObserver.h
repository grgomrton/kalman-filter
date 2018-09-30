#pragma once

#include "IObservableRobot.h"

class IRobotObserver {
public:
    virtual void onRobotMoveCommandReceived(double distance) = 0;
    virtual ~IRobotObserver() = default;
};
