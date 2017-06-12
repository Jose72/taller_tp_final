//
// Created by mbataglia on 23/05/17.
//

#include <iostream>
#include "ClickableButtonGrunt.h"
#include "../common/constants.h"

ClickableButtonGrunt::ClickableButtonGrunt(int x, int y, int width, int height, std::string text,int idUnit)
        : ClickableButton(x, y, width, height, text, idUnit) {

}

void ClickableButtonGrunt::click(Protocol aProtocol) {
    aProtocol.create_unit(idUnit,GRUNT);
    std::cout << "Crear Grunt (Mensaje al server)" << std::endl;
}