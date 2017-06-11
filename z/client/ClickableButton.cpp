//
// Created by mbataglia on 21/05/17.
//

#include <iostream>
#include "ClickableButton.h"
#include "Protocol.h"

ClickableButton::ClickableButton(int x, int y, int width, int height, std::string text,int idUnit):text(std::move(text)) {
    this->x = x;
    this->y = y;
    this->idUnit = idUnit;
    this->width = width;
    this->height = height;
    this->next = 0;
}

ClickableButton::~ClickableButton() {

}

bool ClickableButton::checkBounds(int posX, int posY, Protocol aProtocol) {
    if ( posX >= x && posX <= x+width) {
        if ( posY >= y && posY <= y+height) {
            click(aProtocol);
            return true;
        }
    }
    return false;
}

const std::string &ClickableButton::getText() const {
    return text;
}

int ClickableButton::getX() const {
    return x;
}

int ClickableButton::getY() const {
    return y;
}

int ClickableButton::getWidth() const {
    return width;
}

int ClickableButton::getHeight() const {
    return height;
}
