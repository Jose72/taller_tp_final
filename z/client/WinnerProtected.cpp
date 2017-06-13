//
// Created by mbataglia on 12/06/17.
//

#include "WinnerProtected.h"
#include "../common/Lock.h"
WinnerProtected::WinnerProtected(int winner) {
    this->winner = winner;
}

void WinnerProtected::setWinner(int winner) {
    tLock(this->mut);
    this->winner = winner;
}

int WinnerProtected::getWinner() {
    tLock(this->mut);
    return this->winner;
}
