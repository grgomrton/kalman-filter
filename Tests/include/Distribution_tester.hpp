#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <catch2/catch.hpp>

class Distribution_tester {
public:
    static void check_follows_gaussian(const std::vector<double>& items, double expected_mean, double standard_deviation) {
        // Tested with a one-way table chi square test
        double chi_square_higher_bound = 7.81473;

        double higher_bound_bucket_1 = expected_mean - standard_deviation;
        double higher_bound_bucket_2 = expected_mean;
        double higher_bound_bucket_3 = expected_mean + standard_deviation;

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
};
