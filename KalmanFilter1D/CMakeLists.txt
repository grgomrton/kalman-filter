add_library(KalmanFilter1D
        include/Localizer.h
        src/Localizer.cpp
        include/GaussianNoise.h
        src/GaussianNoise.cpp
        include/GaussianDistributionDescriptor.h
        src/GaussianDistributionDescriptor.cpp)

target_include_directories(KalmanFilter1D PUBLIC include)