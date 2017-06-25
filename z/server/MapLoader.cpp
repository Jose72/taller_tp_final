#include <dirent.h>
#include <iostream>
#include "MapLoader.h"

MapLoader::MapLoader(JsonHandler &json,
                     std::map<int, unit*> &unitsVector,
                     gameMap &map,
                     std::vector<dataMap> &data):
jsonHandler(json),unitsVector(unitsVector),map(map),dataMaps(data){}

void MapLoader::loadListData() {
    loadDirectory("server/maps");
    for (int i = 0; i <this->dataMaps.size() ; ++i) {
        std::cout << this->dataMaps[i].mapName << "\n";
    }
}
void MapLoader::loadDirectory(std::string path) {
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> list_dir;
    std::string mother(path);
    const char * path2 = path.c_str();
    if ((dir = opendir (path2)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string name(ent->d_name);
            if(name.find("data") != std::string::npos){
                list_dir.push_back(name);
            }

        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        //return EXIT_FAILURE;
    }
    std::string temp;
    for (int i = 0; i <list_dir.size(); ++i) {
        for (int j = 0; j <list_dir.size(); ++j) {

            if (list_dir[i] < list_dir[j]) {
                temp = list_dir[j];
                list_dir[j] = list_dir[i];
                list_dir[i] = temp;
            }
        }
    }
    for (int j = 0; j <list_dir.size() ; ++j) {
        std::string full_dir;
        full_dir.append(mother);
        full_dir.append("/");
        full_dir.append(list_dir[j]);
        std::cout<< full_dir <<"\n";
        this->dataMaps.push_back(jsonHandler.jsonToDataMap(full_dir));
    }

}
