//
// Created by mbataglia on 21/05/17.
//

#ifndef Z_CLICKABLEBUTTON_H
#define Z_CLICKABLEBUTTON_H


class ClickableButton {
    private:
        int x;
        int y;
        int width;
        int height;
    public:
        ClickableButton(int x, int y, int width, int height);
        ~ClickableButton();

        void checkBounds(int posX, int posY);

        ClickableButton* next;
};


#endif //Z_CLICKABLEBUTTON_H
