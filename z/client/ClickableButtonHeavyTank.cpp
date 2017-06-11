//
// Created by mbataglia on 11/06/17.
//

#include <iostream>
#include "ClickableButtonHeavyTank.h"
#include "ClickableButton.h"

ClickableButtonHeavyTank::ClickableButtonHeavyTank(int x, int y, int width, int height, std::string text)
        : ClickableButton(x, y, width, height, text) {

}

void ClickableButtonHeavyTank::click(){
    std::cout << "Crear Heavy Tank (Mensaje al server)" << std::endl;
}