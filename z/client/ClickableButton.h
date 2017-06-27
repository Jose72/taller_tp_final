//
// Created by mbataglia on 21/05/17.
//

#ifndef Z_CLICKABLEBUTTON_H
#define Z_CLICKABLEBUTTON_H

#include <string>
#include "Protocol.h"

class ClickableButton {
    private:
        std::string text;
        int x;
        int y;
        int width;
        int height;

    protected:
        int idUnit;
    public:
        ClickableButton(int x, int y, int width, int height, std::string text,int idUnit);
        virtual ~ClickableButton();

        bool checkBounds(int posX, int posY, Protocol aProtocol);

    int getX() const;

    int getY() const;

    const std::string &getText() const;

    virtual void click(Protocol aProtocol) = 0;
    ClickableButton* next;
};


#endif //Z_CLICKABLEBUTTON_H
