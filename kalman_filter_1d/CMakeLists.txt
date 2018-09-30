add_library(KalmanFilter1D
        depr/LocalizerDepr.h
        depr/LocalizerDepr.cpp
        depr/RobotDepr.h
        depr/RobotDepr.cpp
        depr/WorldDepr.h
        depr/WorldDepr.cpp
        depr/GaussianNoiseGeneratorDepr.h
        depr/GaussianNoiseGeneratorDepr.cpp
        depr/IGaussianNoiseGeneratorDepr.h
        depr/ILocalizerDepr.h
        depr/IWorldDepr.h
        src/Localizer.cpp include/Localizer.h src/GaussianNoise.cpp include/GaussianNoise.h)

target_include_directories(KalmanFilter1D PUBLIC include)