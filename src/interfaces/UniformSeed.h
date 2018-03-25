#pragma once

// A seed that provides a uniformly distributed random value in the range [0..1].
class UniformSeed {
public:
    UniformSeed();
    double getNext();
};
