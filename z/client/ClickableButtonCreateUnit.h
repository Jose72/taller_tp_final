//
// Created by mbataglia on 12/06/17.
//

#ifndef Z_CLICKABLEBUTTONCREATEUNIT_H
#define Z_CLICKABLEBUTTONCREATEUNIT_H


#include "ClickableButton.h"

class ClickableButtonCreateUnit : public ClickableButton {
private:
    int unitType;
public:
    ClickableButtonCreateUnit(int x, int y, int width, int height, const std::string &text,int idUnit, int typeUnit);

    void click(Protocol aProtocol);
};


#endif //Z_CLICKABLEBUTTONCREATEUNIT_H
