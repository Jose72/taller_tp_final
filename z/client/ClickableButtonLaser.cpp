//
// Created by mbataglia on 23/05/17.
//

#include <iostream>
#include "ClickableButtonLaser.h"

ClickableButtonLaser::ClickableButtonLaser(int x, int y, int width, int height, const std::string &text ,int idUnit)
        : ClickableButton(x, y, width, height, text,idUnit) {}

void ClickableButtonLaser::click(Protocol aProtocol) {
    std::cout << "Crear Laser (Mensaje al server)" << std::endl;
}