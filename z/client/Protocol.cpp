#include "Protocol.h"
#define CODE_MOVE_UNIT 0
#define CODE_ATTACK 1

Protocol::Protocol(tSocket &s):socket(s) {}

Protocol::~Protocol() {}


void Protocol::moveUnitCS(int cod_unit, int posX, int posY) {
    int CO_to_send = htonl(CODE_MOVE_UNIT);
    int CU_to_send = htonl(cod_unit);
    int PX_to_send = htonl(posX);
    int PY_to_send = htonl((posY));
    socket.send((char*)CO_to_send,sizeof(int));
    socket.send((char*)CU_to_send,sizeof(int));
    socket.send((char*)PX_to_send,sizeof(int));
    socket.send((char*)PY_to_send,sizeof(int));
}

void Protocol::attackUnitCS(int cod_unit, int cod_objective) {
    int CO_to_send = htonl(CODE_ATTACK);
    int CU_to_send = htonl(cod_unit);
    int O_to_send = htonl(cod_objective);
    socket.send((char*)CO_to_send,sizeof(int));
    socket.send((char*)CU_to_send,sizeof(int));
    socket.send((char*)O_to_send,sizeof(int));
    socket.send((char*)O_to_send,sizeof(int));

}