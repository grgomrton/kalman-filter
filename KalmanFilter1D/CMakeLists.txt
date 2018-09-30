add_library(KalmanFilter1D
        include/Localizer.h
        src/Localizer.cpp
        include/Robot.h
        src/Robot.cpp
        include/World.h
        src/World.cpp
        include/NoiseGenerator.h
        src/NoiseGenerator.cpp
        include/IGaussianNoiseGenerator.h
        include/ILocalizer.h
        include/IObservableRobot.h
        include/IRobotObserver.h include/EventDispatcher.h)

target_include_directories(KalmanFilter1D PUBLIC include)