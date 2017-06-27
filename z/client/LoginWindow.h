//
// Created by mbataglia on 26/06/17.
//

#ifndef Z_LOGINWINDOW_H
#define Z_LOGINWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include "../common/Socket.h"
#include "MainWindow.h"

class LoginWindow : public Gtk::Window {
public:
    LoginWindow(tSocket *socket,int argc, char *argv[],
                Glib::RefPtr<Gtk::Application> app);
    Gtk::Box* box;
    Gtk::Button* siguiente;
    Gtk::Entry *entryIp;
    Gtk::Entry *entryPuerto;
    MainWindow *mainWindow;
    Gtk::MessageDialog *messageDialog;
    tSocket* socket;
    void deleteBox();
    virtual ~LoginWindow();
};


#endif //Z_LOGINWINDOW_H
