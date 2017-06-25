//
// Created by mbataglia on 06/06/17.
//

#include <iostream>
#include <SDL_ttf.h>
#include <gtkmm/application.h>
#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include <cstring>

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
#include "MainWindow.h"
#include "ProtocolMenu.h"
#include "TechLevelProtected.h"
#include "SoundManager.h"
#include <SDL_mixer.h>

#define IMAGEPATH "client/sprites/robot1/1.bmp"

#define LEFT_BUTTON 3
#define RIGHT_BUTTON 1
#define WINDOW_H 600
#define WINDOW_W 600
#define PLAYER_INTERFACE_W 300
#define INITIAL_TECH_LEVEL 1
#define NO_WINNER -1

void jugar(Glib::RefPtr<Gtk::Application> app,int argc, char* argv[],MainWindow *pWindow){
    tSocket* socket = pWindow->getSocket();
    int id_client = pWindow->id_client;

    SDL_Surface *screen;

    std::vector<Unit*> u;
    std::map<int, Unit*>um;
    Units_Protected all_units(um);
    bool running = true;
    TechLevelProtected techLevel(INITIAL_TECH_LEVEL);
    WinnerProtected winnerProtected(NO_WINNER);
    SoundManager soundManager(id_client);

    bool waiting_server = true;
    //INICIA SDL Y CREA LA PANTALLA
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0){
        std::cout<<"No se puedo iniciar SDL\n"<< SDL_GetError();
        return;
    }

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Chunk *sonidoMover = Mix_LoadWAV( "sounds/acknowledge_01.wav" );


    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        std::cout<< "No se pudo iniciar SDL_image Error:" << IMG_GetError() << std::endl;
        return;
    }

    if(TTF_Init()==-1) {
        std::cout<< "No se pudo iniciar TTF_Init:" << TTF_GetError() << std::endl;
        return;
    }

    screen = SDL_SetVideoMode(WINDOW_W + PLAYER_INTERFACE_W, WINDOW_H, 32,SDL_HWSURFACE);
    if(screen == NULL){
        std::cout<<"No se puede inicializar el modo grafico\n" <<SDL_GetError();
    }
    atexit(SDL_Quit);
    SpritesPool pool(screen);
    Factory_Units factory(pool);
    Game_map game_map(screen);
    int port_number = atoi(argv[2]);

    //socket->connect(argv[1],port_number);
    std::vector<tThread*> threads;

    ///////////////////////
    //espero confirmacion del server para empezar
    ///////////////////////
    int c = -1;
    socket->receive((char*)&c,4);
    c = ntohl(c);
    if (c == 0) {


        threads.push_back(new TClient_receive(*socket, game_map, all_units, factory, waiting_server, running, id_client,
                                              techLevel, winnerProtected, soundManager));
        threads[0]->start();

        Protocol protocol(*socket, all_units, game_map, factory, techLevel, winnerProtected, soundManager);


        PlayerInterface playerInterface(screen, WINDOW_W, WINDOW_H, PLAYER_INTERFACE_W);

        // while(waiting_server){}

        //sleep(5);
        //main application loop
        threads.push_back(
                new EventHandler(screen, playerInterface, all_units, *socket, game_map, running, factory, id_client,
                                 techLevel, winnerProtected, soundManager));
        threads[1]->start();

        for (int i = 0; i < threads.size(); ++i) {
            threads[i]->join();

        }

    }
    TTF_Quit();
    IMG_Quit();
    app->quit();
}


void on_salir_clicked(Glib::RefPtr<Gtk::Application> app){
    std::cout << "Chau!" << std::endl;
    app->quit();
}

void hideAndPlay(Glib::RefPtr<Gtk::Application> app,int argc, char* argv[],MainWindow *pWindow){
    pWindow->activate_focus();
    pWindow->hide();
    jugar(app,argc,argv,pWindow);
}


void on_map_elegido_crear_clicked(Glib::RefPtr<Gtk::Application> app,int argc, char* argv[],MainWindow *pWindow,std::string map) {
    ProtocolMenu protocolMenu(*(pWindow->socket));
    protocolMenu.sendMapName(map);
    hideAndPlay(app,argc,argv,pWindow);
}

void on_siguiente_crear_clicked(Glib::RefPtr<Gtk::Application> app,int argc, char* argv[],MainWindow *pWindow) {
    ProtocolMenu protocolMenu(*(pWindow->socket));
    int numPlayers = atoi(pWindow->entry->get_text().data());
    int typeGame = 0;
    if( std::strcmp(pWindow->combo->get_active_text().data(), "TEAM_GAME") == 0){
        typeGame = 1;
    }
    int numTeams = atoi(pWindow->combo2->get_active_text().data());
    int response = protocolMenu.createGame(numPlayers,typeGame,numTeams);
    if(response == RESPONSE_PROTOCOL_MENU_OK){
        pWindow->cleanBox();
        std::vector<mapData> mapDatas = protocolMenu.receiveMapsInfo();
        Gtk::Button* buttonMap;
        for(int i = 0; i < mapDatas.size(); i++){
            std::ostringstream texto;
            texto << mapDatas[i].mapName;
            texto << ";";
            texto << mapDatas[i].dimensions;
            texto << ";";
            texto << mapDatas[i].cantEquipos;
            buttonMap = new Gtk::Button(texto.str());
            buttonMap->signal_clicked().connect(sigc::bind(
                    sigc::ptr_fun(on_map_elegido_crear_clicked),
                    app,
                    argc,
                    argv,
                    pWindow,
                    mapDatas[i].mapName));
            pWindow->box->add(*buttonMap);
            pWindow->buttons.push_back(buttonMap);
            texto.clear();
        }
        pWindow->add(*(pWindow->box));
        pWindow->show_all();
    } else {
        std::cout << "Crear juego: " << response << std::endl;
    }
}

void on_crear_clicked(Glib::RefPtr<Gtk::Application> app,int argc, char* argv[],MainWindow *pWindow) {
    ProtocolMenu protocolMenu(*(pWindow->socket));
    int response = protocolMenu.initCreateGame();
    if( response == RESPONSE_PROTOCOL_MENU_OK){
        pWindow->cleanBox();
        pWindow->entry->set_max_length(2);
        pWindow->entry->set_placeholder_text("Cantidad de jugadores");

        pWindow->combo->append("DEATHMATCH");
        pWindow->combo->append("TEAM_GAME");

        pWindow->combo2->append("2");
        pWindow->combo2->append("3");
        pWindow->combo2->append("4");

        pWindow->siguiente->signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_siguiente_crear_clicked), app,argc,argv,pWindow));

        pWindow->box->add(*(pWindow->entry));
        pWindow->box->add(*(pWindow->combo));
        pWindow->box->add(*(pWindow->combo2));
        pWindow->box->add(*(pWindow->siguiente));
        pWindow->box->add(*(pWindow->image));
        pWindow->add(*(pWindow->box));
        pWindow->show_all();
    } else {
        std::cout << "Respuesta server iniciar creacion " << response <<std::endl;
    }

}

void on_siguiente_unirse_clicked(Glib::RefPtr<Gtk::Application> app,int argc, char* argv[],MainWindow *pWindow,int idCreator,int team){
    ProtocolMenu protocolMenu(*(pWindow->socket));
    int response = protocolMenu.joinGame(idCreator, team);
    if(response == RESPONSE_PROTOCOL_MENU_OK){
        hideAndPlay(app,argc,argv,pWindow);
    } else {
        if(response == RESPONSE_PROTOCOL_MENU_FULL_TEAM){
            pWindow->messageDialog->show();
        } else {
            std::cout << "siguiente unirse join game " << response << std::endl;
        }
    }
}

void addButtonDeathMatch(MainWindow *pWindow,
                         InfoGameSelection &infoGame,
                         Glib::RefPtr<Gtk::Application> app,
                         int argc,
                         char **argv){
    std::ostringstream datosPartida;
    datosPartida << "DeathMatch | ";
    datosPartida << "Creador: " << infoGame.idCreator;
    datosPartida << " | Max Jugadores " << infoGame.maxPlayers;
    datosPartida << " | Jugadores " << infoGame.joinedPlayers;
    Gtk::Button* buttonJoin = new Gtk::Button(datosPartida.str());
    buttonJoin->signal_clicked().connect(sigc::bind(
            sigc::ptr_fun(on_siguiente_unirse_clicked),
            app,
            argc,
            argv,
            pWindow,
            infoGame.idCreator,
            NO_TEAM_PARAM));
    pWindow->box->add(*buttonJoin);
    pWindow->buttons.push_back(buttonJoin);
}

void addButtonTeamGame(MainWindow *pWindow,
                         InfoGameSelection &infoGame,
                         int team,
                         Glib::RefPtr<Gtk::Application> app,
                         int argc,
                         char **argv){
    std::ostringstream datosPartida;
    datosPartida << "TeamGame";
    datosPartida << " | Creador: " << infoGame.idCreator;
    datosPartida << " | Equipo " << team;
    datosPartida << " | Max Equipos " << infoGame.numTeams;
    datosPartida << " | Max Jugadores " << infoGame.maxPlayers;
    datosPartida << " | Jugadores " << infoGame.joinedPlayers;
    Gtk::Button* buttonJoin = new Gtk::Button(datosPartida.str());
    buttonJoin->signal_clicked().connect(sigc::bind(
            sigc::ptr_fun(on_siguiente_unirse_clicked),
            app,
            argc,
            argv,
            pWindow,
            infoGame.idCreator,
            team));
    pWindow->box->add(*buttonJoin);
    pWindow->buttons.push_back(buttonJoin);
}

void on_unirse_clicked(Glib::RefPtr<Gtk::Application> app,int argc, char* argv[],MainWindow *pWindow){
    ProtocolMenu protocolMenu(*(pWindow->socket));
    int response = protocolMenu.initJoinGame();
    if( response == RESPONSE_PROTOCOL_MENU_OK){
        protocolMenu.infoJoinGame();
        pWindow->cleanBox();
        for(int i = 0; i < protocolMenu.infoGames.size(); i++){
            if(protocolMenu.infoGames[i]->typeGame == TEAM_GAME){
                for(int j = 1; j <= protocolMenu.infoGames[i]->numTeams; j++){
                    addButtonTeamGame(pWindow, *protocolMenu.infoGames[i], j, app, argc, argv);
                }
            } else {
                addButtonDeathMatch(pWindow, *protocolMenu.infoGames[i], app, argc, argv);
            }
        }
        pWindow->add(*(pWindow->box));
        pWindow->show_all();
    } else{
        std::cout << "respuesta init unirse "<< response << std::endl;
    }
}



void MainWindow::initial(Glib::RefPtr<Gtk::Application> app, int argc, char *argv[]) {
    cleanBox();
    set_default_size(700, 360);
    unirse->signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_unirse_clicked), app,argc,argv,this));
    crear->signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_crear_clicked), app,argc,argv,this));
    salir->signal_clicked().connect(sigc::bind(sigc::ptr_fun(on_salir_clicked), app));
    box->add(*crear);
    box->add(*image);
    box->add(*unirse);
    box->add(*salir);
    add(*box);
    show_all();
}

MainWindow::MainWindow(tSocket *socketParam, int argc, char *argv[], Glib::RefPtr<Gtk::Application> app) {
    socket = socketParam;
    ProtocolMenu protocolMenu(*socket);
    id_client = protocolMenu.receive_id_client();
    createBox();
    initial(app, argc, argv);
}

tSocket *MainWindow::getSocket() {
    return socket;
}

Gtk::Box * MainWindow::getBox() {
    return box;
}

void MainWindow::createBox(){
    box = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0);
    unirse = new Gtk::Button("Unirse");
    crear = new Gtk::Button("Crear");
    salir = new Gtk::Button("Salir");
    siguiente = new Gtk::Button("Siguiente");
    combo = new Gtk::ComboBoxText();
    combo2 = new Gtk::ComboBoxText();
    entry = new Gtk::Entry();
    entry2 = new Gtk::Entry();
    image = new Gtk::Image("client/splash/splash.jpg");
    messageDialog = new Gtk::MessageDialog("Equipo lleno",
                                           false,
                                           Gtk::MessageType::MESSAGE_INFO,
                                           Gtk::ButtonsType::BUTTONS_NONE,
                                           true
    );
}

void MainWindow::deleteBox(){
    delete box;
    delete siguiente;
    delete unirse;
    delete crear;
    delete salir;
    delete combo;
    delete combo2;
    delete entry;
    delete entry2;
    delete image;
    delete messageDialog;

    for (int i = 0; i < buttons.size(); i++){
        delete buttons[i];
    }
    buttons.clear();

}

void MainWindow::cleanBox(){
    deleteBox();
    createBox();
}

MainWindow::~MainWindow() {
    deleteBox();
}
