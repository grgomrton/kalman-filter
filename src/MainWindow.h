#ifndef KALMAN_FILTER_MAINWINDOW_H
#define KALMAN_FILTER_MAINWINDOW_H


#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow(const std::string& greetingText);

private:
    Gtk::Label greeting;
};


#endif //KALMAN_FILTER_MAINWINDOW_H
