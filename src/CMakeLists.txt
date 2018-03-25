link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS} interfaces)

add_executable(kalman_filter Main.cpp MainWindow.cpp GaussianLocalizer.cpp Robot.cpp World.cpp interfaces/IMovingObject.hpp)

target_link_libraries(kalman_filter ${GTKMM_LIBRARIES})