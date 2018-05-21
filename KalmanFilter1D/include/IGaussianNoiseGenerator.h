#pragma once

class IGaussianNoiseGenerator {
public:
    virtual double getNoise(double standardDeviation) = 0;
    virtual ~IGaussianNoiseGenerator() = default;
};
