cmake_minimum_required(VERSION 3.9)
project(KalmanFilter)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(kalman_filter_1d)
add_subdirectory(UI)
add_subdirectory(tests)