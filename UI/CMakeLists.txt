find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GTKMMPLPLOT gtkmm-plplot-2.0)

add_executable(Demo
        src/Main.cpp
        include/MainWindow.h
        src/MainWindow.cpp)

target_include_directories(Demo PRIVATE include ${GTKMM_INCLUDE_DIRS} ${GTKMMPLPLOT_INCLUDE_DIRS})
target_link_libraries(Demo ${GTKMM_LIBRARIES} ${GTKMMPLPLOT_LIBRARIES} KalmanFilter1D)