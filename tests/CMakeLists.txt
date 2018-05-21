add_executable(Tests
        Init.cpp
        TestEnvironmentTests.cpp
        GaussianLocalizerTests.cpp
        RobotTests.cpp
        WorldTests.cpp
        GaussianNoiseProviderTests.cpp)

target_include_directories(Tests PRIVATE include)

target_link_libraries(Tests KalmanFilter1D)

