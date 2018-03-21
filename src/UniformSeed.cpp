#include <cstdlib>
#include <time.h>
#include "UniformSeed.h"

UniformSeed::UniformSeed() {
    srand(time(NULL)); // TODO multiple instantiation?
}

double UniformSeed::getNext() {
    return rand() / (double) RAND_MAX;
}
