#include <GaussianNoiseProvider.h>
#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"

using namespace snowhouse;

TEST_CASE("Gaussian noise generator should have a mean at zero and should follow gaussian distribution", "[random-test]") {
    // Tested with a one-way table chi square test
    std::vector<double> values;
    int sampleSize = 100;
    double higherBoundToKeepNullHypothesis = 7.81473;
    double expectedItemCountInOneStandardDeviationBelowMean = sampleSize * 0.341;
    double expectedItemCountInOneStandardDeviationAboveMean = sampleSize * 0.341;
    double expectedItemCountBelowOneStandardDeviationFromMean = sampleSize * 0.159;
    double expectedItemCountAboveOneStandardDeviationFromMean = sampleSize * 0.159;
    double expectedMean = 0.0;
    double standardDeviation = 0.1;
    auto itemIsBelowOneStandardDeviationBelowMean = [=](double item){ return item < expectedMean - standardDeviation; };
    auto itemIsInOneStandardDeviationBelowMean = [=](double item){ return (item >= expectedMean - standardDeviation) && (item < expectedMean); };
    auto itemIsInOneStandardDeviationAboveMean = [=](double item){ return (item >= expectedMean) && (item < expectedMean + standardDeviation); };
    auto itemIsAboveOneStandardDeviationAboveMean = [=](double item){ return item >= expectedMean + standardDeviation; };
    GaussianNoiseProvider noiseGenerator;

    for (int i=0; i<sampleSize; i++) {
        values.push_back(noiseGenerator.getNoise(standardDeviation));
    }

    auto itemCountBelowOneStandardDeviationBelowMean = std::count_if(values.begin(), values.end(), itemIsBelowOneStandardDeviationBelowMean);
    auto itemCountInOneStandardDeviationBelowMean = std::count_if(values.begin(), values.end(), itemIsInOneStandardDeviationBelowMean);
    auto itemCountInOneStandardDeviationAboveMean = std::count_if(values.begin(), values.end(), itemIsInOneStandardDeviationAboveMean);
    auto itemCountAboveOneStandardDeviationAboveMean = std::count_if(values.begin(), values.end(), itemIsAboveOneStandardDeviationAboveMean);
    auto calculateChiSquare = [](double measured, double expected) { return pow(measured - expected, 2.0) / expected; };
    double chiSquare = 0.0;
    chiSquare += calculateChiSquare(itemCountBelowOneStandardDeviationBelowMean, expectedItemCountBelowOneStandardDeviationFromMean);
    chiSquare += calculateChiSquare(itemCountInOneStandardDeviationBelowMean, expectedItemCountInOneStandardDeviationBelowMean);
    chiSquare += calculateChiSquare(itemCountInOneStandardDeviationAboveMean, expectedItemCountInOneStandardDeviationAboveMean);
    chiSquare += calculateChiSquare(itemCountAboveOneStandardDeviationAboveMean, expectedItemCountAboveOneStandardDeviationFromMean);
    AssertThat(chiSquare, Is().LessThan(higherBoundToKeepNullHypothesis));
}