add_library(KalmanFilter1D
        src/Localizer.cpp
        include/Localizer.h
        src/GaussianNoise.cpp
        include/GaussianNoise.h)

target_include_directories(KalmanFilter1D PUBLIC include)