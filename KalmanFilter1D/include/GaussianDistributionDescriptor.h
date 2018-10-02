#pragma once

struct GaussianDistributionDescriptor {
public:
    double getPosition();

    double getVariance();

    double getAccuracy();

    static GaussianDistributionDescriptor makeFromAccuracy(double position, double accuracy);

    static GaussianDistributionDescriptor makeFromVariance(double position, double variance);

    static double accuracyToVariance(double accuracy);

    static double varianceToAccuracy(double variance);

private:
    GaussianDistributionDescriptor(double position, double variance);

    double _position;
    double _variance;

};