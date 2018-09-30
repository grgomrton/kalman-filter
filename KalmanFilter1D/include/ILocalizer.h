#pragma once

#include "IRobotObserver.h"

class ILocalizer : public IRobotObserver {
public:
    void onRobotMoveCommandReceived(double distance) override = 0;
    virtual void measurementReceived(double position, double accuracy) = 0;
    virtual ~ILocalizer() = default;
};
