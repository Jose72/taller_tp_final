#include <iostream>
#include <SDL_ttf.h>
#include "SDL.h"
#include "Animation.h"
#include "Game_map.h"
#include "SelectionHandler.h"
#include "Factory_Units.h"
#include "../common/Socket.h"
#include "../common/Thread.h"
#include "T_Client.h"
#include "TClient_receive.h"
#include "Units_Protected.h"
#include "ClickableButton.h"
#include "PlayerInterface.h"
#include "EventHandler.h"
#include "ProtocolMenu.h"
#include "MainWindow.h"
#include <gtkmm.h>




int main(int argc, char *argv[]){
    tSocket socket;
    int port_number = atoi(argv[2]);
    socket.connect(argv[1],port_number);
    auto app = Gtk::Application::create();
    MainWindow mainWindow(&socket, argc, argv, app);
    return app->run(mainWindow);
}