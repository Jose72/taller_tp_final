cmake_minimum_required(VERSION 3.7)
project(Client)

set(CMAKE_CXX_STANDARD 11)


INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL REQUIRED sdl)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp Modelo.cpp Modelo.h Game_map.cpp Game_map.h Casillas.cpp Casillas.h Unidades.cpp Unidades.h csprite.cpp csprite.h Animation.cpp Animation.h Flag.cpp Flag.h Fort.cpp Fort.h Unit.cpp Unit.h)
add_executable(Client ${SOURCE_FILES})

target_link_libraries(Client ${SDL_LIBRARIES})

