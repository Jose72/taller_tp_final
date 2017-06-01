#ifndef Z_PROTOCOL_H
#define Z_PROTOCOL_H


#include "../common/Socket.h"

class Protocol {
private:
    tSocket &socket;

public:
    Protocol(tSocket &s);
    ~Protocol();
    void moveUnitCS(int cod_unit, int posX, int posY);
    void attackUnitCS(int cod_unit, int cod_objective);


};


#endif //Z_PROTOCOL_H
