#ifndef KALMAN_FILTER_IMOVINGOBJECT_H
#define KALMAN_FILTER_IMOVINGOBJECT_H

class IMovingObject {
public:
    virtual double getMoveCommandAccuracyInPercentage() = 0;
    virtual ~IMovingObject() = default;
};

#endif //KALMAN_FILTER_IMOVINGOBJECT_H
