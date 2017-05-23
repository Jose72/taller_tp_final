//
// Created by mbataglia on 23/05/17.
//

#include <iostream>
#include "ClickableButtonGrunt.h"

ClickableButtonGrunt::ClickableButtonGrunt(int x, int y, int width, int height, std::string text)
        : ClickableButton(x, y, width, height, text) {

}

void ClickableButtonGrunt::click(){
    std::cout << "Crear Grunt (Mensaje al server)" << std::endl;
}