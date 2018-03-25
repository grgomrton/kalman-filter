#ifndef KALMAN_FILTER_ILOCALIZER_H
#define KALMAN_FILTER_ILOCALIZER_H


class ILocalizer {
public:
    virtual void moveCommandExecuted(double distance) = 0;
    virtual void measurementReceived(double position, double accuracy) = 0;
    virtual ~ILocalizer() = default;
};


#endif //KALMAN_FILTER_ILOCALIZER_H
