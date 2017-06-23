//
// Created by matias on 15/06/17.
//

#ifndef GENMAP_UNITSINMAP_H
#define GENMAP_UNITSINMAP_H


class UnitsInMap {
private:
    int unitCode;
    int posX;
    int posY;
    int owner;

public:
    UnitsInMap(int code, int x, int y, int owner);

    int getUnitCode() const;

    void setUnitCode(int unitCode);

    int getPosX() const;

    void setPosX(int posX);

    int getPosY() const;

    void setPosY(int posY);

    int getOwner() const;

    void setOwner(int owner);





};


#endif //GENMAP_UNITSINMAP_H
