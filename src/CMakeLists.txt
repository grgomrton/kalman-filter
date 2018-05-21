add_library(KalmanFilter1D
        GaussianLocalizer.cpp
        Robot.cpp
        World.cpp
        GaussianNoiseProvider.cpp)

target_include_directories(KalmanFilter1D PUBLIC
        interfaces)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(Demo
        Main.cpp
        MainWindow.cpp)

target_include_directories(Demo PRIVATE interfaces ${GTKMM_INCLUDE_DIRS})
target_link_libraries(Demo KalmanFilter1D ${GTKMM_LIBRARIES})