#pragma once

class IGaussianNoiseProvider {
public:
    virtual double getNoise(double standardDeviation) = 0;
    virtual ~IGaussianNoiseProvider() = default;
};
