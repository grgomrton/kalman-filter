add_library(KalmanFilter1D
        GaussianLocalizer.cpp
        Robot.cpp
        World.cpp
        GaussianNoiseProvider.cpp)

target_include_directories(KalmanFilter1D PUBLIC interfaces headers)