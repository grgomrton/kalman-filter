add_executable(Tests
        tests/Init.cpp
        tests/TestEnvironmentTests.cpp
        tests/LocalizerTests.cpp
        tests/RobotTests.cpp
        tests/WorldTests.cpp
        tests/NoiseGeneratorTests.cpp)

target_include_directories(Tests PRIVATE include)

target_link_libraries(Tests KalmanFilter1D)

