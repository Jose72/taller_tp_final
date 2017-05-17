#include "SpritesPool.h"
#include <vector>
#include "Animation.h"

SpritesPool::SpritesPool(SDL_Surface *screen) {
    this->screen = screen;
    //BLUE GRUNT
    std::vector<Animation*> b_grunt;
    Animation *grunt_blue0 = new Animation(this->screen,
                                      "/home/matias/Escritorio/Client/sprites/robot1/0.bmp",
                                      16,16);
    b_grunt.push_back(grunt_blue0);
    Animation*grunt_blue1= new Animation(this->screen,
                                    "/home/matias/Escritorio/Client/sprites/robot1/1.bmp",
                                    16,16);
    b_grunt.push_back(grunt_blue1);
    this->pool[BLUE_GRUNT] = b_grunt;

    //COLORLESS FLAG

    std::vector<Animation*> c_flag;
    Animation *flag0 = new Animation(this->screen,
                                     "/home/matias/Escritorio/Client/sprites/flags/0.bmp",
                                     16,16);
    c_flag.push_back(flag0);
    Animation*flag1 = new Animation(this->screen,
                                    "/home/matias/Escritorio/Client/sprites/flags/1.bmp",
                                    16,16);
    c_flag.push_back(flag1);
    Animation *flag2 = new Animation(this->screen,
                                     "/home/matias/Escritorio/Client/sprites/flags/2.bmp",
                                     16,16);
    c_flag.push_back(flag2);
    Animation*flag3 = new Animation(this->screen,
                                    "/home/matias/Escritorio/Client/sprites/flags/3.bmp",
                                    16,16);
    c_flag.push_back(flag3);
    this->pool[COLORLESS_FLAG] = c_flag;


}

std::vector<Animation*> SpritesPool::get_animations(FlagsUnitType flag) {
    return this->pool[flag];
}