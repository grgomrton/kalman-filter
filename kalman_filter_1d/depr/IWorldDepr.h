#pragma once

class IWorldDepr {
public:
    virtual void onRobotMoveCommandReceived(double distance) = 0;
    virtual ~IWorldDepr() = default;
};