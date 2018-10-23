find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GTKMMPLPLOT gtkmm-plplot-2.0)

add_library(
        KalmanFilterLibrary

        src/estimated_position.cpp
        include/estimated_position.h
        src/gaussian_noise.cpp
        include/gaussian_noise.h
        src/localizer.cpp
        include/localizer.h
        src/plot_functions.cpp
        include/plot_functions.h
        src/sensor.cpp include/sensor.h src/robot.cpp include/robot.h)
target_include_directories(KalmanFilterLibrary PUBLIC include)

add_executable(
        Demo

        src/application.cpp
        include/demo_window.h
        src/demo_window.cpp
        src/plotter.cpp
        include/plotter.h
)
target_include_directories(Demo PRIVATE include ${GTKMM_INCLUDE_DIRS} ${GTKMMPLPLOT_INCLUDE_DIRS})
target_link_libraries(Demo KalmanFilterLibrary ${GTKMM_LIBRARIES} ${GTKMMPLPLOT_LIBRARIES})