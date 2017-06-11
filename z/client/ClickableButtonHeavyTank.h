//
// Created by mbataglia on 11/06/17.
//

#ifndef Z_CLICKABLEBUTTONHEAVYTANK_H
#define Z_CLICKABLEBUTTONHEAVYTANK_H


#include "ClickableButton.h"

class ClickableButtonHeavyTank : public ClickableButton {
public:
    ClickableButtonHeavyTank(int x, int y, int width, int height, std::string text,int idUnit);

    void click(Protocol aProtocol);
};


#endif //Z_CLICKABLEBUTTONHEAVYTANK_H
