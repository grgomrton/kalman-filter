cmake_minimum_required(VERSION 3.9)
project(KalmanFilter)
set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GTKMMPLPLOT gtkmm-plplot-2.0)

add_executable(Demo
        src/Main.cpp
        include/MainWindow.h
        src/MainWindow.cpp
        src/Plotter.cpp
        include/Plotter.h
        src/Estimated_position.cpp
        include/Estimated_position.h
        src/GaussianNoise.cpp
        include/GaussianNoise.h
        src/Localizer.cpp
        include/Localizer.h
        src/Plot_functions.cpp
        include/Plot_functions.h)
target_include_directories(Demo PRIVATE include ${GTKMM_INCLUDE_DIRS} ${GTKMMPLPLOT_INCLUDE_DIRS})
target_link_libraries(Demo ${GTKMM_LIBRARIES} ${GTKMMPLPLOT_LIBRARIES})

add_executable(Tests
        test/Init.cpp
        src/Localizer.cpp
        include/Localizer.h
        src/Estimated_position.cpp
        include/Estimated_position.h
        test/LocalizerTests.cpp
        src/GaussianNoise.cpp
        include/GaussianNoise.h
        test/GaussianNoiseTests.cpp
        src/Plot_functions.cpp
        include/Plot_functions.h
        test/Plot_functions_tests.cpp)
target_include_directories(Tests PRIVATE include test/include)
target_link_libraries(Tests)
