//
// Created by mbataglia on 12/06/17.
//

#ifndef Z_WINNERPROTECTED_H
#define Z_WINNERPROTECTED_H


#include <mutex>

class WinnerProtected {
private:
    std::mutex mut;
    int winner;

public:
    WinnerProtected(int winner);
    void setWinner(int winner);
    int getWinner();

};

#endif //Z_WINNERPROTECTED_H
