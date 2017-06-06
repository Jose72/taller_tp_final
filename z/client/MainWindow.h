//
// Created by mbataglia on 06/06/17.
//

#ifndef Z_MAINWINDOW_H
#define Z_MAINWINDOW_H


#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include "../common/Socket.h"

class MainWindow : public Gtk::Window{
private:
    Gtk::Box box;
    Gtk::Button unirse;
    Gtk::Button crear;
    Gtk::Button salir;
    Gtk::Entry entry;
    Gtk::Entry nombre;
    Gtk::ComboBoxText combo;
public:
    MainWindow(tSocket & socket, int argc, char *argv[], Glib::RefPtr<Gtk::Application> ptr);

};


#endif //Z_MAINWINDOW_H
