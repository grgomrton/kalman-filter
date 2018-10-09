find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GTKMMPLPLOT gtkmm-plplot-2.0)

add_library(
        KalmanFilterLibrary

        src/Estimated_position.cpp
        include/Estimated_position.h
        src/Gaussian_noise.cpp
        include/Gaussian_noise.h
        src/Localizer.cpp
        include/Localizer.h
        src/Plot_functions.cpp
        include/Plot_functions.h
)
target_include_directories(KalmanFilterLibrary PUBLIC include)

add_executable(
        Demo

        src/Main.cpp
        include/Main_window.h
        src/Main_window.cpp
        src/Plotter.cpp
        include/Plotter.h
)
target_include_directories(Demo PRIVATE include ${GTKMM_INCLUDE_DIRS} ${GTKMMPLPLOT_INCLUDE_DIRS})
target_link_libraries(Demo KalmanFilterLibrary ${GTKMM_LIBRARIES} ${GTKMMPLPLOT_LIBRARIES})