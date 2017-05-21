cmake_minimum_required(VERSION 3.5)
project(z)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")



INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL REQUIRED sdl)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS})

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


add_executable(cliente ${SOURCE_FILES_CLIENT})
add_executable(server ${SOURCE_FILES_SERVER})

target_link_libraries(cliente ${SDL_LIBRARIES})