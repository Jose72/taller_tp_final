#include "SpritesPool.h"
#include <vector>
#include <dirent.h>
#include "Animation.h"

SpritesPool::SpritesPool(SDL_Surface *screen) {
    this->screen = screen;
    this->load_sprites("client/sprites/robot1",
                       BLUE_GRUNT,
                       GREEN_GRUNT,
                       RED_GRUNT,
                       YELLOW_GRUNT);

    this->load_sprites("client/sprites/grunt_fire",
                       FIRE_BLUE_GRUNT,
                       FIRE_GREEN_GRUNT,
                       FIRE_RED_GRUNT,
                       FIRE_YELLOW_GRUNT);

    this->load_sprites("client/sprites/laser_fire",
                       FIRE_LASER_BLUE,
                       FIRE_LASER_GREEN,
                       FIRE_LASER_RED,
                       FIRE_LASER_YELLOW);

    this->load_sprites("client/sprites/psycho_fire",
                       FIRE_PSYCHO_BLUE,
                       FIRE_PSYCHO_GREEN,
                       FIRE_PSYCHO_RED,
                       FIRE_PSYCHO_YELLOW);

    this->load_sprites("client/sprites/pyro_fire",
                       FIRE_PYRO_BLUE,
                       FIRE_PYRO_GREEN,
                       FIRE_PYRO_RED,
                       FIRE_PYRO_YELLOW);

    this->load_sprites("client/sprites/sniper_fire",
                       FIRE_SNIPER_BLUE,
                       FIRE_SNIPER_GREEN,
                       FIRE_SNIPER_RED,
                       FIRE_SNIPER_YELLOW);

    this->load_sprites("client/sprites/tought_fire",
                       FIRE_TOUGHT_BLUE,
                       FIRE_TOUGHT_GREEN,
                       FIRE_TOUGHT_RED,
                       FIRE_TOUGHT_YELLOW);

    this->load_sprites("client/sprites/die",
                       DIE_BLUE_GRUNT,
                       DIE_GREEN_GRUNT,
                       DIE_RED_GRUNT,
                       DIE_YELLOW_GRUNT);

    this->load_sprites("client/sprites/beer",
                       BEER_BLUE,
                       BEER_GREEN,
                       BEER_RED,
                       BEER_YELLOW);

    this->load_sprites("client/sprites/celebrate",
                       CELEBRATE_BLUE,
                       CELEBRATE_GREEN,
                       CELEBRATE_RED,
                       CELEBRATE_YELLOW);

    this->load_sprites_with_null("client/sprites/flags",
                                 COLORLESS_FLAG,
                                 BLUE_FLAG,
                                 GREEN_FLAG,
                                 RED_FLAG,
                                 YELLOW_FLAG);

    this->load_sprites_with_dim("client/sprites/missile_launcher",
                                MISILE_LAUNCHER_BLUE,
                                MISILE_LAUNCHER_GREEN,
                                MISILE_LAUNCHER_RED,
                                MISILE_LAUNCHER_YELLOW,
                                32);

    this->load_sprites_with_dim("client/sprites/mlStand",
                                MISILE_LAUNCHER_BLUE_STAND,
                                MISILE_LAUNCHER_GREEN_STAND,
                                MISILE_LAUNCHER_RED_STAND,
                                MISILE_LAUNCHER_YELLOW_STAND,
                                32);

    this->load_sprite("client/sprites/missile_launcher",MISILE_LAUNCHER_EMPTY,"empty",32,32);

    this->load_sprites_with_dim("client/sprites/heavyTank",
                                HEAVY_TANK_BLUE,
                                HEAVY_TANK_GREEN,
                                HEAVY_TANK_RED,
                                HEAVY_TANK_YELLOW,
                                32);

    this->load_sprites_with_dim("client/sprites/heavyStand",
                                HEAVY_TANK_BLUE_STAND,
                                HEAVY_TANK_GREEN_STAND,
                                HEAVY_TANK_RED_STAND,
                                HEAVY_TANK_YELLOW_STAND,
                                32);
    this->load_sprite("client/sprites/heavyTank",HEAVY_TANK_EMPTY,"empty",32,32);

    this->load_sprites_with_dim("client/sprites/mediumTank",
                                MEDIUM_TANK_BLUE,
                                MEDIUM_TANK_GREEN,
                                MEDIUM_TANK_RED,
                                MEDIUM_TANK_YELLOW,
                                32);

    this->load_sprites_with_dim("client/sprites/mediumStand",
                                MEDIUM_TANK_BLUE_STAND,
                                MEDIUM_TANK_GREEN_STAND,
                                MEDIUM_TANK_RED_STAND,
                                MEDIUM_TANK_YELLOW_STAND,
                                32);

    this->load_sprite("client/sprites/mediumTank",MEDIUM_TANK_EMPTY,"empty",32,32);

    this->load_sprites_with_dim("client/sprites/lightTank",
                                LIGHT_TANK_BLUE,
                                LIGHT_TANK_GREEN,
                                LIGHT_TANK_RED,
                                LIGHT_TANK_YELLOW,
                                32);

    this->load_sprites_with_dim("client/sprites/lightStand",
                                LIGHT_TANK_BLUE_STAND,
                                LIGHT_TANK_GREEN_STAND,
                                LIGHT_TANK_RED_STAND,
                                LIGHT_TANK_YELLOW_STAND,
                                32);

    this->load_sprite("client/sprites/lightTank",LIGHT_TANK_EMPTY,"empty",32,32);

    this->load_sprites_with_dim("client/sprites/jeep",
                                JEEP_BLUE,
                                JEEP_GREEN,
                                JEEP_RED,
                                JEEP_YELLOW,
                                32);

    this->load_sprites_with_dim("client/sprites/jeepStand",
                                JEEP_BLUE_STAND,
                                JEEP_GREEN_STAND,
                                JEEP_RED_STAND,
                                JEEP_YELLOW_STAND,
                                32);

    this->load_sprite("client/sprites/jeep",JEEP_EMPTY,"empty",32,32);

    this->load_sprite("client/sprites/laserBullet",
                      LASER_BULLET,
                      "laser",
                      16, 16);

    this->load_sprite("client/sprites/pyroBullet",
                      PYRO_BULLET,
                      "bullet",
                      16, 16);

    this->load_sprite("client/sprites/toughtBullet",
                      TOUGHT_BULLET,
                      "bullet",
                      16, 16);

    this->load_sprite("client/sprites/fire",
                      BULLET_DEAD,
                      "fire",
                      16, 16);

    this->load_sprite("client/sprites/fuerte",
                      FORT_ALIVE,
                      "alive",
                      160, 192);

    this->load_sprite("client/sprites/fuerte",
                      FORT_DEAD,
                      "destroyed",
                      160, 192);

    this->load_sprite("client/sprites/fabrica_robots",
                      FACTORY_ROBOTS_ALIVE,
                      "alive",
                      80, 80);

    this->load_sprite("client/sprites/fabrica_robots",
                      FACTORY_ROBOTS_DEAD,
                      "destroyed",
                      80, 80);

    this->load_sprite("client/sprites/fabrica_vehiculos",
                      FACTORY_VEHICLES_ALIVE,
                      "alive",
                      80, 80);

    this->load_sprite("client/sprites/fabrica_vehiculos",
                      FACTORY_VEHICLES_DEAD,
                      "destroyed",
                      80, 80);

    this->load_sprite("client/sprites/bridgeCH",BRIDGE_CONCRETE_HORIZONTAL,"bridge",64,64);
    this->load_sprite("client/sprites/bridgeCH",BRIDGE_CONTRETE_HORIZONTAL_DESTROYED,"destroyed",64,64);
    this->load_sprite("client/sprites/bridgeCV",BRIDGE_CONCRETE_VERTICAL,"bridge",64,64);
    this->load_sprite("client/sprites/bridgeCV",BRIDGE_CONTRETE_VERTICAL_DESTROYED,"destroyed",64,64);

    this->load_sprite("client/sprites/bridgeWH",BRIDGE_WOOD_HORIZONTAL,"bridge",64,64);
    this->load_sprite("client/sprites/bridgeWH",BRIDGE_WOOD_HORIZONTAL_DESTROYED,"destroyed",64,64);
    this->load_sprite("client/sprites/bridgeWV",BRIDGE_WOOD_VERTICAL,"bridge",64,64);
    this->load_sprite("client/sprites/bridgeWV",BRIDGE_WOOD_VERTICAL_DESTROYED,"destroyed",64,64);
    this->load_sprite("client/sprites/iceBlock",ICE_BLOCK,"ice",32,32);
    this->load_sprite("client/sprites/rock",ROCK_BLOCK,"rock",32,32);
}




std::vector<Animation*> & SpritesPool::get_animations(FlagsUnitType flag) {
    return this->pool[flag];
}

void SpritesPool::load_sprites(std::string path,
                               FlagsUnitType blue,
                               FlagsUnitType green,
                               FlagsUnitType red,
                               FlagsUnitType yellow) {

    DIR *dir;
    struct dirent *ent;
    std::vector<Animation*> b_grunt,g_grunt,r_grunt,y_grunt;
    std::vector<std::string> list_dir;
    std::string mother(path);
    const char * path2 = path.c_str();
    if ((dir = opendir (path2)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string name(ent->d_name);
            list_dir.push_back(name);
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
    for (int j = 2; j <list_dir.size() ; ++j) {
        std::string full_dir;
        full_dir.append(mother);
        full_dir.append("/");
        full_dir.append(list_dir[j]);
        char * full_dirNoConst = const_cast<char*> (full_dir.c_str());
        Animation *robot_move = new Animation(this->screen,full_dirNoConst,16,16);
        if(list_dir[j].find("blue") != std::string::npos){
            b_grunt.push_back(robot_move);
        }else if(list_dir[j].find("green") != std::string::npos){
            g_grunt.push_back(robot_move);
        }else if(list_dir[j].find("red") != std::string::npos){
            r_grunt.push_back(robot_move);
        }else if(list_dir[j].find("yellow") != std::string::npos){
            y_grunt.push_back(robot_move);
        }
    }
    this->pool[blue] = b_grunt;
    this->pool[red] = r_grunt;
    this->pool[green] = g_grunt;
    this->pool[yellow] = y_grunt;
}

void SpritesPool::load_sprites_with_null(std::string path,
                                         FlagsUnitType null,
                                         FlagsUnitType blue,
                                         FlagsUnitType green,
                                         FlagsUnitType red,
                                         FlagsUnitType yellow) {

    DIR *dir;
    struct dirent *ent;
    std::vector<Animation*> n_grunt,b_grunt,g_grunt,r_grunt,y_grunt;
    std::vector<std::string> list_dir;
    std::string mother(path);
    const char * path2 = path.c_str();
    if ((dir = opendir (path2)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string name(ent->d_name);
            list_dir.push_back(name);
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
    for (int j = 2; j <list_dir.size() ; ++j) {
        std::string full_dir;
        full_dir.append(mother);
        full_dir.append("/");
        full_dir.append(list_dir[j]);
        char * full_dirNoConst = const_cast<char*> (full_dir.c_str());
        Animation *robot_move = new Animation(this->screen,full_dirNoConst,16,16);
        if(list_dir[j].find("blue") != std::string::npos){
            b_grunt.push_back(robot_move);
        }else if(list_dir[j].find("green") != std::string::npos){
            g_grunt.push_back(robot_move);
        }else if(list_dir[j].find("red") != std::string::npos){
            r_grunt.push_back(robot_move);
        }else if(list_dir[j].find("yellow") != std::string::npos){
            y_grunt.push_back(robot_move);
        }else if(list_dir[j].find("null") != std::string::npos){
            n_grunt.push_back(robot_move);
        }
    }
    this->pool[blue] = b_grunt;
    this->pool[red] = r_grunt;
    this->pool[green] = g_grunt;
    this->pool[yellow] = y_grunt;
    this->pool[null] = n_grunt;
}

void SpritesPool::load_sprites_with_dim(std::string path,
                                        FlagsUnitType blue,
                                        FlagsUnitType green,
                                        FlagsUnitType red,
                                        FlagsUnitType yellow,
                                        int dimensions) {
    DIR *dir;
    struct dirent *ent;
    std::vector<Animation*> b_grunt,g_grunt,r_grunt,y_grunt;
    std::vector<std::string> list_dir;
    std::string mother(path);
    const char * path2 = path.c_str();
    if ((dir = opendir (path2)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string name(ent->d_name);
            list_dir.push_back(name);
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
    for (int j = 2; j <list_dir.size() ; ++j) {
        std::string full_dir;
        full_dir.append(mother);
        full_dir.append("/");
        full_dir.append(list_dir[j]);
        char * full_dirNoConst = const_cast<char*> (full_dir.c_str());
        Animation *robot_move = new Animation(this->screen,full_dirNoConst,dimensions,dimensions);
        if(list_dir[j].find("blue") != std::string::npos){
            b_grunt.push_back(robot_move);
        }else if(list_dir[j].find("green") != std::string::npos){
            g_grunt.push_back(robot_move);
        }else if(list_dir[j].find("red") != std::string::npos){
            r_grunt.push_back(robot_move);
        }else if(list_dir[j].find("yellow") != std::string::npos){
            y_grunt.push_back(robot_move);
        }
    }
    this->pool[blue] = b_grunt;
    this->pool[red] = r_grunt;
    this->pool[green] = g_grunt;
    this->pool[yellow] = y_grunt;

}

void SpritesPool::load_sprite(std::string path,
                              FlagsUnitType flag,
                              std::string keyword,
                                int x, int y) {

    DIR *dir;
    struct dirent *ent;
    std::vector<Animation*> aAnimation;
    std::vector<std::string> list_dir;
    std::string mother(path);
    const char * path2 = path.c_str();
    if ((dir = opendir (path2)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string name(ent->d_name);
            list_dir.push_back(name);
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
    for (int j = 2; j <list_dir.size() ; ++j) {
        std::string full_dir;
        full_dir.append(mother);
        full_dir.append("/");
        full_dir.append(list_dir[j]);
        char * full_dirNoConst = const_cast<char*> (full_dir.c_str());
        Animation *robot_move = new Animation(this->screen,full_dirNoConst,x,y);
        if(list_dir[j].find(keyword) != std::string::npos){
            aAnimation.push_back(robot_move);

        }
    }
    this->pool[flag] = aAnimation;
}