#pragma once

class ILocalizer {
public:
    virtual void moveCommandExecuted(double distance) = 0;
    virtual void measurementReceived(double position, double accuracy) = 0;
    virtual ~ILocalizer() = default;
};
