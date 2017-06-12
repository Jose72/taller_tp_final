//
// Created by mbataglia on 12/06/17.
//

#include <iostream>
#include "ClickableButtonCreateUnit.h"

#include "../common/constants.h"

ClickableButtonCreateUnit::ClickableButtonCreateUnit(int x, int y, int width, int height, std::string text,int idUnit,int unitType)
        : ClickableButton(x, y, width, height, text, idUnit),unitType(unitType) {

}

void ClickableButtonCreateUnit::click(Protocol aProtocol) {
    aProtocol.create_unit(idUnit,unitType);
    std::cout << "Crear " << unitType << " (Mensaje al server)" << std::endl;
}