link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS}  )

add_executable(kalman_filter main.cpp)

target_link_libraries(kalman_filter
        ${GTKMM_LIBRARIES}  )