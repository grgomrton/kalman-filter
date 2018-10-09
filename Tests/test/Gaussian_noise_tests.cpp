#include <catch2/catch.hpp>
#include <Distribution_tester.hpp>
#include "Gaussian_noise.h"

TEST_CASE("Two values obtained from noise generator should be different", "[random-test]") {
    auto standard_deviation = 3.0;
    Gaussian_noise noiseGenerator;

    auto first_item = noiseGenerator.get_noise(standard_deviation);
    auto second_item = noiseGenerator.get_noise(standard_deviation);

    CHECK(!(first_item == Approx(second_item)));
}

TEST_CASE("Gaussian noise values should follow gaussian distribution with mean at zero and standard deviation as specified", "[random-test]") {
    unsigned int sample_size = 100;
    std::vector<double> values(sample_size);
    double expected_mean = 0.0;
    double expected_standard_deviation = 0.1;
    Gaussian_noise noise_generator;

    for (int i = 0; i < sample_size; i++) {
        values[i] = noise_generator.get_noise(expected_standard_deviation);
    }

    Distribution_tester::check_follows_gaussian(values, expected_mean, expected_standard_deviation);
}