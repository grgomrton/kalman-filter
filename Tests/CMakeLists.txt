add_executable(
        Tests

        test/init.cpp
        test/localizer.cpp
        test/gaussian_noise.cpp
        test/plot_functions.cpp test/sensor.cpp include/distribution_validator.hpp)
target_include_directories(Tests PRIVATE include)
target_link_libraries(Tests KalmanFilterLibrary)