#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"
#include "../src/UniformSeed.h" // TODO add include library (?)

using namespace snowhouse;

TEST_CASE("The value provided by the seed should be between 0 and 1 (inclusive)") {
    UniformSeed seed;

    double value = seed.getNext();

    AssertThat(value, Is().GreaterThanOrEqualTo(0.0));
    AssertThat(value, Is().LessThanOrEqualTo(1.0));
}

TEST_CASE("Two consecutive values acquired should differ") {
    UniformSeed seed;

    auto firstValue = seed.getNext();
    auto nextValue = seed.getNext();

    AssertThat(nextValue, Is().GreaterThan(firstValue).Or().LessThan(firstValue));
}

TEST_CASE("The distribution does not differ on a statistically significant level of 5% from the uniform distribution", "[sporadic]") {
    UniformSeed seed;
    std::vector<double> values;
    int sampleSize = 1000;
    double higherBoundForChiSquareToKeepTheNullHypothesis = 7.81473;
    double cuttingPointOfFirstBucketExclusive = 0.2;
    double cuttingPointOfSecondBucketExclusive = 0.4;
    double cuttingPointOfThirdBucketExclusive = 0.6;
    double cuttingPointOfFourthBucketExclusive = 0.8;
    double expectedValueCountInFirstBucket = 200.0;
    double expectedValueCountInSecondBucket = 200.0;
    double expectedValueCountInThirdBucket = 200.0;
    double expectedValueCountInFourthBucket = 200.0;
    double expectedValueCountInFifthBucket = 200.0;

    for (int i=0; i<sampleSize; i++) {
        values.push_back(seed.getNext());
    }

    double valueCountInFirstBucket = std::count_if(values.begin(), values.end(), [cuttingPointOfFirstBucketExclusive](double value){ return (value>=0.0) && (value<cuttingPointOfFirstBucketExclusive); });
    double valueCountInSecondBucket = std::count_if(values.begin(), values.end(), [cuttingPointOfFirstBucketExclusive,cuttingPointOfSecondBucketExclusive](double value){ return (value>=cuttingPointOfFirstBucketExclusive) && (value<cuttingPointOfSecondBucketExclusive); });
    double valueCountInThirdBucket = std::count_if(values.begin(), values.end(), [cuttingPointOfSecondBucketExclusive,cuttingPointOfThirdBucketExclusive](double value){ return (value>=cuttingPointOfSecondBucketExclusive) && (value<cuttingPointOfThirdBucketExclusive); });
    double valueCountInFourthBucket = std::count_if(values.begin(), values.end(), [cuttingPointOfThirdBucketExclusive,cuttingPointOfFourthBucketExclusive](double value){ return (value>=cuttingPointOfThirdBucketExclusive) && (value<cuttingPointOfFourthBucketExclusive); });
    double valueCountInFifthBucket = std::count_if(values.begin(), values.end(), [cuttingPointOfFourthBucketExclusive](double value){ return (value>=cuttingPointOfFourthBucketExclusive) && (value<=1.0); });
    double diffInBucket1 = pow(expectedValueCountInFirstBucket - valueCountInFirstBucket, 2.0) / expectedValueCountInFirstBucket;
    double diffInBucket2 = pow(expectedValueCountInSecondBucket - valueCountInSecondBucket, 2.0) / expectedValueCountInSecondBucket;
    double diffInBucket3 = pow(expectedValueCountInThirdBucket - valueCountInThirdBucket, 2.0) / expectedValueCountInThirdBucket;
    double diffInBucket4 = pow(expectedValueCountInFourthBucket - valueCountInFourthBucket, 2.0) / expectedValueCountInFourthBucket;
    double diffInBucket5 = pow(expectedValueCountInFifthBucket - valueCountInFifthBucket, 2.0) / expectedValueCountInFifthBucket;
    double chiSquare = diffInBucket1 + diffInBucket2 + diffInBucket3 + diffInBucket4 + diffInBucket5;
    AssertThat(chiSquare, Is().LessThanOrEqualTo(higherBoundForChiSquareToKeepTheNullHypothesis));
}