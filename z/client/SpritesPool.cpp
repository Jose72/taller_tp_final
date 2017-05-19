#include "SpritesPool.h"
#include <vector>
#include "Animation.h"

SpritesPool::SpritesPool(SDL_Surface *screen) {
    this->screen = screen;
    //BLUE GRUNT
    std::vector<Animation*> b_grunt;

    Animation *grunt_blue0 = new Animation(this->screen,"client/sprites/robot1/bw000.bmp",16,16);
    b_grunt.push_back(grunt_blue0);

    Animation*grunt_blue1= new Animation(this->screen,"client/sprites/robot1/bw001.bmp",16,16);
    b_grunt.push_back(grunt_blue1);

    Animation *grunt_blue2 = new Animation(this->screen,"client/sprites/robot1/bw002.bmp",16,16);
    b_grunt.push_back(grunt_blue2);

    Animation*grunt_blue3= new Animation(this->screen,"client/sprites/robot1/bw003.bmp",16,16);
    b_grunt.push_back(grunt_blue3);

    Animation *grunt_blue4 = new Animation(this->screen,"client/sprites/robot1/bw450.bmp",16,16);
    b_grunt.push_back(grunt_blue4);

    Animation*grunt_blue5= new Animation(this->screen,"client/sprites/robot1/bw451.bmp",16,16);
    b_grunt.push_back(grunt_blue5);

    Animation *grunt_blue6 = new Animation(this->screen,"client/sprites/robot1/bw452.bmp",16,16);
    b_grunt.push_back(grunt_blue6);

    Animation*grunt_blue7= new Animation(this->screen,"client/sprites/robot1/bw453.bmp",16,16);
    b_grunt.push_back(grunt_blue7);

    Animation *grunt_blue8 = new Animation(this->screen,"client/sprites/robot1/bw900.bmp",16,16);
    b_grunt.push_back(grunt_blue8);

    Animation*grunt_blue9= new Animation(this->screen,"client/sprites/robot1/bw901.bmp",16,16);
    b_grunt.push_back(grunt_blue9);

    Animation *grunt_blue10 = new Animation(this->screen,"client/sprites/robot1/bw902.bmp",16,16);
    b_grunt.push_back(grunt_blue10);

    Animation*grunt_blue11= new Animation(this->screen,"client/sprites/robot1/bw903.bmp",16,16);
    b_grunt.push_back(grunt_blue11);

    Animation *grunt_blue12 = new Animation(this->screen,"client/sprites/robot1/bw1350.bmp",16,16);
    b_grunt.push_back(grunt_blue12);

    Animation*grunt_blue13= new Animation(this->screen,"client/sprites/robot1/bw1351.bmp",16,16);
    b_grunt.push_back(grunt_blue13);

    Animation *grunt_blue14 = new Animation(this->screen,"client/sprites/robot1/bw1352.bmp",16,16);
    b_grunt.push_back(grunt_blue14);

    Animation*grunt_blue15= new Animation(this->screen,"client/sprites/robot1/bw1353.bmp",16,16);
    b_grunt.push_back(grunt_blue15);

    Animation *grunt_blue16 = new Animation(this->screen,"client/sprites/robot1/bw1800.bmp",16,16);
    b_grunt.push_back(grunt_blue16);

    Animation*grunt_blue17= new Animation(this->screen,"client/sprites/robot1/bw1801.bmp",16,16);
    b_grunt.push_back(grunt_blue17);

    Animation *grunt_blue18 = new Animation(this->screen,"client/sprites/robot1/bw1802.bmp",16,16);
    b_grunt.push_back(grunt_blue18);

    Animation*grunt_blue19= new Animation(this->screen,"client/sprites/robot1/bw1803.bmp",16,16);
    b_grunt.push_back(grunt_blue19);

    Animation *grunt_blue20 = new Animation(this->screen,"client/sprites/robot1/bw2250.bmp",16,16);
    b_grunt.push_back(grunt_blue20);

    Animation*grunt_blue21= new Animation(this->screen,"client/sprites/robot1/bw2251.bmp",16,16);
    b_grunt.push_back(grunt_blue21);

    Animation *grunt_blue22 = new Animation(this->screen,"client/sprites/robot1/bw2252.bmp",16,16);
    b_grunt.push_back(grunt_blue22);

    Animation*grunt_blue23= new Animation(this->screen,"client/sprites/robot1/bw2253.bmp",16,16);
    b_grunt.push_back(grunt_blue23);

    Animation *grunt_blue24 = new Animation(this->screen,"client/sprites/robot1/bw2700.bmp",16,16);
    b_grunt.push_back(grunt_blue24);

    Animation*grunt_blue25= new Animation(this->screen,"client/sprites/robot1/bw2701.bmp",16,16);
    b_grunt.push_back(grunt_blue25);

    Animation *grunt_blue26 = new Animation(this->screen,"client/sprites/robot1/bw2702.bmp",16,16);
    b_grunt.push_back(grunt_blue26);

    Animation*grunt_blue27= new Animation(this->screen,"client/sprites/robot1/bw2703.bmp",16,16);
    b_grunt.push_back(grunt_blue27);

    Animation *grunt_blue28 = new Animation(this->screen,"client/sprites/robot1/bw3150.bmp",16,16);
    b_grunt.push_back(grunt_blue28);

    Animation*grunt_blue29= new Animation(this->screen,"client/sprites/robot1/bw3151.bmp",16,16);
    b_grunt.push_back(grunt_blue29);

    Animation *grunt_blue30 = new Animation(this->screen,"client/sprites/robot1/bw3152.bmp",16,16);
    b_grunt.push_back(grunt_blue30);

    Animation*grunt_blue31= new Animation(this->screen,"client/sprites/robot1/bw3153.bmp",16,16);
    b_grunt.push_back(grunt_blue31);

    this->pool[BLUE_GRUNT] = b_grunt;

    //COLORLESS FLAG

    std::vector<Animation*> c_flag;
    Animation *flag0 = new Animation(this->screen,
                                     "client/sprites/flags/0.bmp",
                                     16,16);
    c_flag.push_back(flag0);
    Animation*flag1 = new Animation(this->screen,
                                    "client/sprites/flags/1.bmp",
                                    16,16);
    c_flag.push_back(flag1);
    Animation *flag2 = new Animation(this->screen,
                                     "client/sprites/flags/2.bmp",
                                     16,16);
    c_flag.push_back(flag2);
    Animation*flag3 = new Animation(this->screen,
                                    "client/sprites/flags/3.bmp",
                                    16,16);
    c_flag.push_back(flag3);
    this->pool[COLORLESS_FLAG] = c_flag;

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
    this->pool[FORT] = fort;
}




std::vector<Animation*> SpritesPool::get_animations(FlagsUnitType flag) {
    return this->pool[flag];
}