#include "SpritesPool.h"
#include <vector>
#include <dirent.h>
#include "Animation.h"

SpritesPool::SpritesPool(SDL_Surface *screen) {
    this->screen = screen;
    this->load_sprites("client/sprites/robot1",BLUE_GRUNT,GREEN_GRUNT,RED_GRUNT,YELLOW_GRUNT);
    this->load_sprites("client/sprites/grunt_fire",FIRE_BLUE_GRUNT,FIRE_GREEN_GRUNT,FIRE_RED_GRUNT,FIRE_YELLOW_GRUNT);
    this->load_sprites("client/sprites/laser_fire",FIRE_LASER_BLUE,FIRE_LASER_GREEN,FIRE_LASER_RED,FIRE_LASER_YELLOW);
    this->load_sprites("client/sprites/die",DIE_BLUE_GRUNT,DIE_GREEN_GRUNT,DIE_RED_GRUNT,DIE_YELLOW_GRUNT);
    this->load_sprites("client/sprites/beer",BEER_BLUE,BEER_GREEN,BEER_RED,BEER_YELLOW);
    this->load_sprites("client/sprites/celebrate",CELEBRATE_BLUE,CELEBRATE_GREEN,CELEBRATE_RED,CELEBRATE_YELLOW);
    this->load_sprites_with_null("client/sprites/flags",COLORLESS_FLAG,BLUE_FLAG,GREEN_FLAG,RED_FLAG,YELLOW_FLAG);
    this->load_sprites_with_dim("client/sprites/missile_launcher", MISILE_LAUNCHER_BLUE,MISILE_LAUNCHER_GREEN,MISILE_LAUNCHER_RED,MISILE_LAUNCHER_YELLOW,32);


    //FORT

    std::vector<Animation*> fort;
    Animation *fort_alive = new Animation(this->screen,
                                          "client/sprites/fuertes/alive.bmp",
                                          160,192);
    fort.push_back(fort_alive);
    Animation*fort_death = new Animation(this->screen,
                                         "client/sprites/fuertes/death.bmp",
                                         160,192);
    fort.push_back(fort_death);
    this->pool[FORT_SPRITE] = fort;
}




std::vector<Animation*> SpritesPool::get_animations(FlagsUnitType flag) {
    return this->pool[flag];
}

void SpritesPool::load_sprites(char *path,
                               FlagsUnitType blue,
                               FlagsUnitType green,
                               FlagsUnitType red,
                               FlagsUnitType yellow) {

    DIR *dir;
    struct dirent *ent;
    std::vector<Animation*> b_grunt,g_grunt,r_grunt,y_grunt;
    std::vector<std::string> list_dir;
    std::string mother(path);
    if ((dir = opendir (path)) != NULL) {
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

void SpritesPool::load_sprites_with_null(char *path,
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
    if ((dir = opendir (path)) != NULL) {
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

void SpritesPool::load_sprites_with_dim(char *path,
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
    if ((dir = opendir (path)) != NULL) {
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