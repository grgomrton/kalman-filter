find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(Demo
        src/Main.cpp
        include/MainWindow.h
        src/MainWindow.cpp)

target_include_directories(Demo PRIVATE include ${GTKMM_INCLUDE_DIRS})
target_link_libraries(Demo ${GTKMM_LIBRARIES})