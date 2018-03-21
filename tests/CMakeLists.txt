project(kalman_filter_tests)

include_directories(include)

add_executable(kalman_filter_tests Init.cpp TestEnvironmentTests.cpp UniformSeedTests.cpp ../src/UniformSeed.cpp ../src/UniformSeed.h) # todo some more sophisticated method for including sources?
