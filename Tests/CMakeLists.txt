add_executable(Tests
        src/Init.cpp
        src/LocalizerTests.cpp
        src/GaussianNoiseTests.cpp)

target_include_directories(Tests PRIVATE include)

target_link_libraries(Tests KalmanFilter1D)

