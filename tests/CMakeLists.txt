add_executable(Tests
        src/Init.cpp
        depr/TestEnvironmentTestsDepr.cpp
        depr/LocalizerTestsDepr.cpp
        depr/RobotTestsDepr.cpp
        depr/WorldTestsDepr.cpp
        depr/NoiseGeneratorTestsDepr.cpp src/LocalizerTests.cpp src/GaussianNoiseTests.cpp)

target_include_directories(Tests PRIVATE include)

target_link_libraries(Tests KalmanFilter1D)

