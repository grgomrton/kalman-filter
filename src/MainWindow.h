#ifndef KALMAN_FILTER_MAINWINDOW_H
#define KALMAN_FILTER_MAINWINDOW_H

#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow(const char* greetingText);

    ~MainWindow() override;
};

#endif //KALMAN_FILTER_MAINWINDOW_H
