add_library(KalmanFilter1D
        include/GaussianLocalizer.h
        src/GaussianLocalizer.cpp
        include/Robot.h
        src/Robot.cpp
        include/World.h
        src/World.cpp
        include/GaussianNoiseProvider.h
        src/GaussianNoiseProvider.cpp
        include/IGaussianNoiseProvider.h
        include/ILocalizer.h
        include/IMovingObject.h
        include/IMovingObjectPositionStore.h)

target_include_directories(KalmanFilter1D PUBLIC include)