add_executable(
        Tests

        test/Init.cpp
        test/Localizer_tests.cpp
        test/Gaussian_noise_tests.cpp
        test/Plot_functions_tests.cpp)
target_include_directories(Tests PRIVATE include)
target_link_libraries(Tests KalmanFilterLibrary)