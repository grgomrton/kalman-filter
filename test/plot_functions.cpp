#include <catch2/catch.hpp>
#include "plot_functions.h"

TEST_CASE("Uniform scale should be equally distributed between start and end inclusive") {
    auto start = 0.0;
    auto end = 20.0;
    auto itemCount = 11;

    auto scale = plot_functions::create_uniform_scale(start, end, itemCount);

    CHECK(scale.size() == itemCount);
    CHECK(scale.front() == Approx(start));
    CHECK(scale.back() == Approx(end));
    CHECK(scale[2] == Approx(4.0));
    CHECK(scale[5] == Approx(10.0));
    CHECK(scale[9] == Approx(18.0));
}

TEST_CASE("Gaussian plot should follow gaussian curve values") {
    // using plot from http://www.visiondummy.com/2014/03/divide-variance-n-1/
    auto mean = 10.0;
    auto stddev = 3.0;
    auto variance = 9.0;
    auto eps = 0.01;
    auto itemCount = 21;

    auto scale = plot_functions::create_uniform_scale(0.0, 20.0, itemCount);
    auto plot = plot_functions::plot_gaussian(mean, variance, scale);

    CHECK(plot[10] == Approx(0.133).epsilon(eps));
    CHECK(plot[7] == Approx(0.08).epsilon(eps));
    CHECK(plot[13] == Approx(0.08).epsilon(eps));
    CHECK(plot[4] == Approx(0.018).epsilon(eps));
    CHECK(plot[16] == Approx(0.018).epsilon(eps));
}

