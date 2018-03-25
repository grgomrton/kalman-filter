#ifndef KALMAN_FILTER_IROBOTPOSITIONMAINTAINER_H
#define KALMAN_FILTER_IROBOTPOSITIONMAINTAINER_H


class IRobotPositionMaintainer {
public:
    virtual void moveCommandExecuted(double distance) = 0;
    virtual ~IRobotPositionMaintainer() = default;
};


#endif //KALMAN_FILTER_IROBOTPOSITIONMAINTAINER_H
