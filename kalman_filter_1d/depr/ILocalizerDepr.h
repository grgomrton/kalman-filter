#pragma once

class ILocalizerDepr {
public:
    virtual void onRobotMoveCommandReceived(double distance) = 0;
    virtual void measurementReceived(double position, double accuracy) = 0;
    virtual ~ILocalizerDepr() = default;
};
