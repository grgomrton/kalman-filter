project(kalman_filter_tests)

include_directories(include ../src/interfaces)

add_executable(kalman_filter_tests Init.cpp TestEnvironmentTests.cpp UniformSeedTests.cpp ../src/UniformSeed.cpp PositionEstimatorTests.cpp ../src/PositionEstimator.cpp RobotTests.cpp ../src/Robot.cpp) # todo better linking to implementations?
