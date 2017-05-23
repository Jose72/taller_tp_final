//
// Created by mbataglia on 21/05/17.
//

#ifndef Z_CLICKABLEBUTTON_H
#define Z_CLICKABLEBUTTON_H

#include <string>

class ClickableButton {
    private:
        int x;
        int y;
        int width;
        int height;
        std::string text;
    public:
        ClickableButton(int x, int y, int width, int height, std::string text);
        ~ClickableButton();

        bool checkBounds(int posX, int posY);

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;

    const std::string &getText() const;

    virtual void click() = 0;
    ClickableButton* next;
};


#endif //Z_CLICKABLEBUTTON_H
