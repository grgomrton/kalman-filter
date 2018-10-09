#include <catch2/catch.hpp>
#include "Gaussian_noise.h"

// Tested with a one-way table chi square test
static void check_follows_gaussian(const std::vector<double>& items, double expected_mean, double expected_standard_deviation) {
    double chi_square_higher_bound = 7.81473;

    double higher_bound_bucket_1 = -expected_standard_deviation;
    double higher_bound_bucket_2 = expected_mean;
    double higher_bound_bucket_3 = +expected_standard_deviation;

    double expected_bucket_1_size = items.size() * 0.159;
    double expected_bucket_2_size = items.size() * 0.341;
    double expected_bucket_3_size = items.size() * 0.341;
    double expected_bucket_4_size = items.size() * 0.159;

    auto in_bucket_1 = [&](double item) { return (item < higher_bound_bucket_1); };
    auto in_bucket_2 = [&](double item) { return (item >= higher_bound_bucket_1) && (item < higher_bound_bucket_2); };
    auto in_bucket_3 = [&](double item) { return (item >= higher_bound_bucket_2) && (item < higher_bound_bucket_3); };
    auto in_bucket_4 = [&](double item) { return (item >= higher_bound_bucket_3); };

    auto bucket_1_size = std::count_if(begin(items), end(items), in_bucket_1);
    auto bucket_2_size = std::count_if(begin(items), end(items), in_bucket_2);
    auto bucket_3_size = std::count_if(begin(items), end(items), in_bucket_3);
    auto bucket_4_size = std::count_if(begin(items), end(items), in_bucket_4);

    auto squared_error = [](double measured, double expected) { return pow(measured - expected, 2.0) / expected; };
    double measured_chi_square = 0.0;
    measured_chi_square += squared_error(bucket_1_size, expected_bucket_1_size);
    measured_chi_square += squared_error(bucket_2_size, expected_bucket_2_size);
    measured_chi_square += squared_error(bucket_3_size, expected_bucket_3_size);
    measured_chi_square += squared_error(bucket_4_size, expected_bucket_4_size);

    CHECK(measured_chi_square < chi_square_higher_bound);
}

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

    check_follows_gaussian(values, expected_mean, expected_standard_deviation);
}