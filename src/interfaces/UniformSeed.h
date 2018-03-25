#ifndef KALMAN_FILTER_RANDOMSEED_H
#define KALMAN_FILTER_RANDOMSEED_H


// A seed that provides a uniformly distributed random value in the range [0..1].
class UniformSeed {
public:
    UniformSeed();
    double getNext();
};


#endif //KALMAN_FILTER_RANDOMSEED_H
