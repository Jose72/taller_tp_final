cmake_minimum_required(VERSION 3.7)
project(z)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")



INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(GTKMM REQUIRED gtkmm-3.0)
INCLUDE_DIRECTORIES(${GTKMM_INCLUDE_DIRS})

PKG_SEARCH_MODULE(SDL REQUIRED sdl)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS})

PKG_SEARCH_MODULE(SDL_IMAGE REQUIRED SDL_image)
INCLUDE_DIRECTORIES( ${SDL_IMAGE_INCLUDE_DIR})

PKG_SEARCH_MODULE(SDL_TTF REQUIRED SDL_ttf)
INCLUDE_DIRECTORIES( ${SDL_TTF_INCLUDE_DIR})


file(GLOB SOURCE_FILES_CLIENT
        client/*.cpp
        client/*.h
        common/*.cpp
        common/*.h
        )

file(GLOB SOURCE_FILES_SERVER
        server/*.cpp
        server/*.h
        common/*.cpp
        common/*.h
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(clientGame ${SOURCE_FILES_CLIENT})
add_executable(serverGame ${SOURCE_FILES_SERVER})

target_link_libraries(clientGame ${GTKMM_LIBRARIES} ${SDL_LIBRARIES} ${SDL_IMAGE_LIBRARIES} ${SDL_TTF_LIBRARIES})
