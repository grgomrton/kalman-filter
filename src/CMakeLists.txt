link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(kalman_filter Main.cpp MainWindow.cpp MainWindow.h UniformSeed.cpp UniformSeed.h)

target_link_libraries(kalman_filter ${GTKMM_LIBRARIES})