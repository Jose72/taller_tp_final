//
// Created by mbataglia on 26/06/17.
//

#include <gtkmm/application.h>
#include <iostream>
#include "LoginWindow.h"

void on_siguiente_clicked(Glib::RefPtr<Gtk::Application> app, int argc, char *argv[], LoginWindow *pWindow) {
    try{
        int port_number = atoi(pWindow->entryPuerto->get_text().data());
        pWindow->socket->connect(pWindow->entryIp->get_text().data(),port_number);
        app->hold();
        pWindow->hide();
        pWindow->mainWindow = new MainWindow(pWindow->socket, argc, argv, app);
    } catch (std::runtime_error){
        pWindow->messageDialog->show();
    }

}

LoginWindow::LoginWindow(tSocket *socketParam, int argc, char *argv[], Glib::RefPtr<Gtk::Application> app) {
    socket = socketParam;
    mainWindow = nullptr;
    messageDialog = new Gtk::MessageDialog("No se encontro servidor",
                                           false,
                                           Gtk::MessageType::MESSAGE_INFO,
                                           Gtk::ButtonsType::BUTTONS_NONE,
                                           true
    );
    box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0);
    siguiente = new Gtk::Button("Siguiente");
    entryIp = new Gtk::Entry();
    entryPuerto = new Gtk::Entry();
    entryIp->set_max_length(50);
    entryIp->set_placeholder_text("Ingrese IP servidor");
    entryPuerto->set_max_length(6);
    entryPuerto->set_placeholder_text("Ingrese Puerto servidor");
    siguiente->signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_siguiente_clicked),app,argc,argv,this));
    box->add(*entryIp);
    box->add(*entryPuerto);
    box->add(*siguiente);
    add(*box);
    set_default_size(400, 90);
    show_all();
}

void LoginWindow::deleteBox() {
    delete box;
    delete siguiente;
    delete entryIp;
    delete entryPuerto;
    delete messageDialog;
    if(mainWindow != nullptr){
        delete mainWindow;
    }

}

LoginWindow::~LoginWindow() {
    deleteBox();
}