//
// Created by mbataglia on 11/06/17.
//

#ifndef Z_CLICKABLEBUTTONJEEP_H
#define Z_CLICKABLEBUTTONJEEP_H


#include "ClickableButton.h"

class ClickableButtonJeep : public ClickableButton {
public:
    ClickableButtonJeep(int x, int y, int width, int height, std::string text,int idUnit);
    void click(Protocol aProtocol);
};


#endif //Z_CLICKABLEBUTTONJEEP_H
