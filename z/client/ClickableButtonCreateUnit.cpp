//
// Created by mbataglia on 12/06/17.
//

#include <iostream>
#include "ClickableButtonCreateUnit.h"

#include "../common/constants.h"

ClickableButtonCreateUnit::ClickableButtonCreateUnit(int x,
                                                     int y,
                                                     int width,
                                                     int height,
                                                     const std::string &text,
                                                     int idUnit,
                                                     int unitType,
                                                     std::map<int,int> &creating)
        : ClickableButton(x, y, width, height, text, idUnit),unitType(unitType),creating(creating) {

}

void ClickableButtonCreateUnit::click(Protocol aProtocol) {
    aProtocol.create_unit(idUnit,unitType);
    creating[idUnit] = unitType;
}