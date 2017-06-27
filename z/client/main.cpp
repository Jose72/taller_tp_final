#include <iostream>
#include "Game_map.h"
#include "SelectionHandler.h"
#include "../common/Thread.h"
#include "MainWindow.h"
#include "LoginWindow.h"
#include <gtkmm.h>


int main(int argc, char *argv[]){
    auto app = Gtk::Application::create();
    tSocket socket;
    LoginWindow loginWindow(&socket,argc,argv,app);
    return app->run(loginWindow);
}