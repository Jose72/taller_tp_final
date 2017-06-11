//
// Created by mbataglia on 11/06/17.
//

#include <iostream>
#include "ClickableButtonJeep.h"
#include "ClickableButton.h"

ClickableButtonJeep::ClickableButtonJeep(int x, int y, int width, int height, std::string text)
        : ClickableButton(x, y, width, height, text) {

}

void ClickableButtonJeep::click(){
    std::cout << "Crear Jeep (Mensaje al server)" << std::endl;
}