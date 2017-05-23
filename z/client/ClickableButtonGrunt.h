//
// Created by mbataglia on 23/05/17.
//

#ifndef Z_CLICKABLEBUTTONGRUNT_H
#define Z_CLICKABLEBUTTONGRUNT_H


#include "ClickableButton.h"
#include <string>
class ClickableButtonGrunt : public ClickableButton {
public:
    ClickableButtonGrunt(int x, int y, int width, int height, std::string text);

    void click();
};


#endif //Z_CLICKABLEBUTTONGRUNT_H
