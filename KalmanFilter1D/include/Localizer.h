#pragma once

#include <cmath>

struct pos_est {
public:
    double position() { return _position; }

    double covariance() { return _covariance; }

    double accuracy() { return covarianceToAccuracy(_covariance); }

    static pos_est make_from_accuracy(double position, double accuracy) { // todo test
        return pos_est(position, accuracy_to_covariance(accuracy));
    }

    static pos_est make_from_covariance(double position, double covariance) {
        return pos_est(position, covariance);
    }

    static double accuracy_to_covariance(double accuracy) {
        auto standardDeviation = accuracy / 2.0;
        return pow(standardDeviation, 2.0);
    }

    static double covarianceToAccuracy(double covariance) {
        return sqrt(covariance) * 2.0;
    }

private:
    pos_est(double position, double covariance) : _position(position), _covariance(covariance) {}

    double _position;
    double _covariance;

};

class Localizer {
public:
    explicit Localizer(pos_est initial_position);

    pos_est movementUpdate(double distance, double accuracy_percentage);

    pos_est measurementUpdate(double measured_position, double absolute_accuracy);

    pos_est getPosition();

private:
    pos_est _position;

    static double calcMultiplier(double percentage);

    static double calcAccuracy(double distance, double accuracy_percentage);

};
