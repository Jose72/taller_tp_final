#include <iostream>
#include <SDL_ttf.h>
#include "SDL.h"
#include "Animation.h"
#include "Game_map.h"
#include "SelectionHandler.h"
#include "Factory_Units.h"
#include "../common/Socket.h"
#include "../common/Thread.h"
#include "TClient_receive.h"
#include "Units_Protected.h"
#include "ClickableButton.h"
#include "PlayerInterface.h"
#include "EventHandler.h"
#include "ProtocolMenu.h"
#include "MainWindow.h"
#include "LoginWindow.h"
#include <gtkmm.h>




int main(int argc, char *argv[]){
    auto app = Gtk::Application::create();
    tSocket socket;
    LoginWindow loginWindow(&socket,argc,argv,app);
    return app->run(loginWindow);
}