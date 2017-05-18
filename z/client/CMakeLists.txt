cmake_minimum_required(VERSION 3.7)
project(Client)

set(CMAKE_CXX_STANDARD 11)


INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL REQUIRED sdl)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp Game_map.cpp Game_map.h Casillas.cpp Casillas.h Animation.cpp Animation.h Unit.cpp Unit.h T_Client.cpp T_Client.h SelectionHandler.cpp SelectionHandler.h SpritesPool.cpp SpritesPool.h Factory_Units.cpp Factory_Units.h Camera.cpp Camera.h EventHandler.cpp EventHandler.h)
add_executable(Client ${SOURCE_FILES})

target_link_libraries(Client ${SDL_LIBRARIES})

