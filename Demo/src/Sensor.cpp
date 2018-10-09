#include <Estimated_position.h>
#include <Sensor.h>

const double Sensor::sensor_accuracy_in_metres = 4.9;

Sensor::Sensor()
    : noise_standard_deviation(sensor_accuracy_in_metres / 2.0) {
}

double Sensor::get_noisy_measurement(double position) {
    return position + noise_generator.get_noise(noise_standard_deviation);
}

double Sensor::get_accuracy() {
    return sensor_accuracy_in_metres;
}
