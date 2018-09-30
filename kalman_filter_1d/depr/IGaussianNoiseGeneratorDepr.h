#pragma once

class IGaussianNoiseGeneratorDepr {
public:
    virtual double getNoise(double standardDeviation) = 0;
    virtual ~IGaussianNoiseGeneratorDepr() = default;
};
