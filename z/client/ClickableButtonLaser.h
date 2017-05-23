//
// Created by mbataglia on 23/05/17.
//

#ifndef Z_CLICKABLEBUTTONLASER_H
#define Z_CLICKABLEBUTTONLASER_H


#include "ClickableButton.h"

class ClickableButtonLaser : public ClickableButton {
public:
    ClickableButtonLaser(int x, int y, int width, int height, const std::string &text);
    void click();
};


#endif //Z_CLICKABLEBUTTONLASER_H
