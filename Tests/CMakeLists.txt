add_executable(
        Tests

        test/Init.cpp
        test/Localizer_tests.cpp
        test/Gaussian_noise_tests.cpp
        test/Plot_functions_tests.cpp test/Sensor_tests.cpp include/Distribution_tester.hpp)
target_include_directories(Tests PRIVATE include)
target_link_libraries(Tests KalmanFilterLibrary)