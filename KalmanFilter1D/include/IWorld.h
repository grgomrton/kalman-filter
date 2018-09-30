#pragma once

class IWorld {
public:
    virtual void onRobotMoveCommandReceived(double distance) = 0;
    virtual ~IWorld() = default;
};