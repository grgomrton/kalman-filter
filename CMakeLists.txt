cmake_minimum_required(VERSION 3.9)
project(kalman_filter)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(src)
add_subdirectory(tests)