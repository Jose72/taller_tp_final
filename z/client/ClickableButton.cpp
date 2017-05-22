//
// Created by mbataglia on 21/05/17.
//

#include <iostream>
#include "ClickableButton.h"

ClickableButton::ClickableButton(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;

    this->width = width;
    this->height = height;

    this->next = 0;
}

ClickableButton::~ClickableButton() {

}

void ClickableButton::checkBounds(int posX, int posY) {
    if ( posX >= x && posX <= x+width) {
        if ( posY >= y && posY <= y+height) {
            std::cout << "click" << std::endl;
        }
    } else {
        std::cout << "no" << std::endl;
    }
}