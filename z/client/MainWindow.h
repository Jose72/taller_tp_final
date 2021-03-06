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
#include <SDL_mixer.h>
#include <gtkmm/messagedialog.h>
#include "../common/Socket.h"

class MainWindow : public Gtk::Window{
public:
    Gtk::Box* box;
    Gtk::Button* unirse;
    Gtk::Button* crear;
    Gtk::Button* salir;
    Gtk::Button* siguiente;
    Gtk::Entry *entry;
    Gtk::Entry *entry2;
    Gtk::Image* image;
    Gtk::Entry nombre;
    Gtk::ComboBoxText *combo;
    Gtk::ComboBoxText *combo2;
    Gtk::MessageDialog *messageDialog;
    tSocket* socket;
    std::vector<Gtk::Button*> buttons;
    int id_client;

public:

    MainWindow(tSocket *socket, int argc, char *argv[], Glib::RefPtr<Gtk::Application> ptr);

    tSocket *getSocket();

    void initial(Glib::RefPtr<Gtk::Application> app, int argc, char **argv);

    void cleanBox();

    virtual ~MainWindow();

    void createBox();

    void deleteBox();
};


#endif //Z_MAINWINDOW_H