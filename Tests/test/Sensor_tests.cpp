#include <catch2/catch.hpp>
#include <Sensor.h>
#include <Distribution_tester.hpp>

TEST_CASE("Sensor measurement should follow gaussian distribution around the position with a standard deviation half a regular smartphone gps accuracy", "[random-test]") {
    double position = 3.0;
    double expected_std_dev = 2.45;
    double expected_mean = 3.0;
    unsigned int sample_size = 1000;
    std::vector<double> measurements(sample_size);
    Sensor sensor;

    for (int i=0; i<sample_size; i++) {
        measurements[i] = sensor.get_noisy_measurement(position);
    }

    Distribution_tester::check_follows_gaussian(measurements, expected_mean, expected_std_dev);
}