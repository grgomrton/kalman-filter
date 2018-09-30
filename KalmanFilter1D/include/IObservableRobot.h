#pragma once

class IObservableRobot {
public:
    virtual double getMoveCommandAccuracyInPercentage() const = 0;
    virtual ~IObservableRobot() = default;
};
