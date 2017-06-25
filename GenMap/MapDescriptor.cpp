#include <iostream>
#include <random>
#include "MapDescriptor.h"

#define MIN 1
#define MAX 8
#define SUBDIM 10
#define CODE_PASTO 0
#define CODE_AGUA 1
#define CODE_LAVA 2
#define CODE_NIEVE 3
#define CODE_ASFALTO 4
#define CODE_PANTANO 5
#define CODE_TIERRA 6
#define CODE_CARRETERA 7
#define CODE_GRUNT 0
#define CODE_PSYCHO 1
#define CODE_TOUGHT 2
#define CODE_PYRO 3
#define CODE_SNIPER 4
#define CODE_LAZER 5
#define CODE_JEEP 6
#define CODE_MEDIUM_TANK 7
#define CODE_LIGHT_TANK 8
#define CODE_HEAVY_TANK 9
#define CODE_MML 10
#define FORT_CODE 11
#define CODE_RF 12
#define CODE_VF 13
#define CODE_FLAG 14
#define CODE_BRIDGEV 20
#define CODE_BRIDGE 21
#define CODE_ROCK 22
#define CODE_ICEB 23
#define TWO_TEAMS 2
#define THREE_TEAMS 3
#define FOUR_TEAMS 4
#define MAP_INDEX_CONST_TERRAIN 50
#define MAX_DIM 210


MapDescriptor::MapDescriptor(int lado,
                             int equipos,
                             int cantTerritorios,
                             std::vector<int> &techLevels,
                             int vehiculosAbandonados,
                             std::vector<int> &unidadesIniciales,
                             int setTiles):techLevels(techLevels),unidadesIniciales(unidadesIniciales) {
    this->lado = lado;
    this->cantEquipos = equipos;
    this->cantTerritorios = cantTerritorios;
    this->cantVehiculosAbandonados = vehiculosAbandonados;
    this->setTiles = setTiles;

}

std::vector<int> MapDescriptor::generate() {
    createDescriptor(this->cantEquipos, this->setTiles);
    std::vector<int> descriptor = randomize2();
    assingVehicles();
    return  descriptor;

}

/*
    SET VOLCANICO              (CARRETERA-LAVA)        1
    SET_PANTANO                (PANTANO-AGUA)        2
    SET_CIUDAD                 (CARRETERA-ASFALTO)   3
    SET_INVERNAL               (NIEVE-AGUA)          4
    SET_HIELOyFUEGO            (NIEVE-LAVA)          5
    SET_PANTANO_VOLCANICO      (PANTANO_LAVA)        6
    SET_FULL_CARRETERA         (CARRETERA)           7
    SET_FULL_NIEVE             (NIEVE)               8
    SET_FULL_PANTANO           (PANTANO)             9
    SET_FULL_TIERRA            (TIERRA)              10
*/
void MapDescriptor::createDescriptor(int equipos, int setTiles){
    int tileBase1 = 0;
    int tileBase2 = 0;
    switch(setTiles){
        case 1:
            tileBase1 = CODE_CARRETERA;
            tileBase2 = CODE_LAVA;
            break;
        case 2:
            tileBase1 = CODE_PANTANO;
            tileBase2 = CODE_AGUA;
            break;
        case 3:
            tileBase1 =CODE_ASFALTO;
            tileBase2 = CODE_CARRETERA;
            break;
        case 4:
            tileBase1 = CODE_NIEVE;
            tileBase2 = CODE_AGUA;
            break;
        case 5:
            tileBase1 = CODE_NIEVE;
            tileBase2 = CODE_LAVA;
            break;
        case 6:
            tileBase1 = CODE_PANTANO;
            tileBase2 = CODE_LAVA;
            break;
        case 7:
            tileBase1 = CODE_CARRETERA;
            tileBase2 = CODE_CARRETERA;
            break;
        case 8:
            tileBase1 = CODE_NIEVE;
            tileBase2 = CODE_NIEVE;
            break;
        case 9:
            tileBase1 = CODE_PANTANO;
            tileBase2 = CODE_PANTANO;
            break;
        case 10:
            tileBase1 = CODE_TIERRA;
            tileBase2 = CODE_TIERRA;
            break;
    }
    int indiceBase = 89;
    for (int i = 1; i <=equipos ; ++i) {
        this->subDescriptors[indiceBase+i] = base(i);
    }
    this->subDescriptors[1] = random1(tileBase1,tileBase2);
    this->subDescriptors[2] = random2(tileBase1,tileBase2);
    this->subDescriptors[3] = random3(tileBase1,tileBase2);
    this->subDescriptors[4] = random4(tileBase1,tileBase2);
    this->subDescriptors[5] = random5(tileBase1,tileBase2);
    this->subDescriptors[6] = random6(tileBase1,tileBase2);
    this->subDescriptors[7] = random7(tileBase1,tileBase2);
    this->subDescriptors[8] = random8(tileBase1,tileBase2);
    int c = MAP_INDEX_CONST_TERRAIN;
    this->subDescriptors[c+1] = random1_terrain(tileBase1,tileBase2);
    this->subDescriptors[c+2] = random2_terrain(tileBase1,tileBase2);
    this->subDescriptors[c+3] = random3_terrain(tileBase1,tileBase2);
    this->subDescriptors[c+4] = random4_terrain(tileBase1,tileBase2);
    this->subDescriptors[c+5] = random5_terrain(tileBase1,tileBase2);
    this->subDescriptors[c+6] = random6_terrain(tileBase1,tileBase2);
    this->subDescriptors[c+7] = random7_terrain(tileBase1,tileBase2);
    this->subDescriptors[c+8] = random8_terrain(tileBase1,tileBase2);
}

std::vector<int> MapDescriptor::randomize2() {
    int techLevelCounter = 0;
    int territoriosCounter = 1;
    int dim = lado*SUBDIM;
    int descriptorFinal[MAX_DIM][MAX_DIM];
    for (int i = 0; i <lado ; ++i) {
        for (int j = 0; j <lado ; ++j) {
            int subKey = obtenerCase();
            if(territoriosCounter > cantTerritorios){
                subKey = subKey + MAP_INDEX_CONST_TERRAIN;
            }
            territoriosCounter++;
            subKey = obtenerSubKey(i,j,subKey);
            int x1 = i*SUBDIM;
            int x2 = x1+SUBDIM;
            int y1 = j*SUBDIM;
            int y2 = y1+SUBDIM;
            int subDescrip [SUBDIM][SUBDIM];
            for (int p = 0; p <SUBDIM ; ++p) {
                for (int q = 0; q <SUBDIM; ++q) {
                    subDescrip[p][q] = this->subDescriptors[subKey].descriptor[p][q];
                }
            }
            assingUnits(i,j,subKey,techLevelCounter);

            for (int m = 0; m <dim ; ++m) {
                for (int n = 0; n < dim; ++n) {
                    if((m >= x1) && (m < x2) && (n >= y1) && (n < y2)){
                       descriptorFinal[m][n] = subDescrip[m-x1][n-y1];
                    }
                }
            }
        }

    }
    std::vector<int> desVec;
    for (int i = 0; i <dim ; ++i) {
        for (int j = 0; j <dim ; ++j) {
            desVec.push_back(descriptorFinal[i][j]);
        }
    }
    std::cout<<"\n";

    return desVec;

}
int MapDescriptor::obtenerSubKey(int i, int j, int subKey) {
    if(cantEquipos == TWO_TEAMS){
        if((i==0) && (j== 0)){
            subKey = 90;
        }
        if((i==(lado-1)) && (j==(lado-1))){
            subKey = 91;
        }
    }
    if(cantEquipos==THREE_TEAMS){
        if((i==0) && (j== 0)){
            subKey = 90;
        }
        if((i==(lado-1)) && (j==(lado-1))){
            subKey = 91;
        }
        if((i==0) && (j==(lado-1))){
            subKey = 92;
        }
    }
    if(cantEquipos == FOUR_TEAMS){
        if((i==0) && (j== 0)){
            subKey = 90;
        }
        if((i==0) && (j==(lado-1))){
            subKey = 91;
        }
        if((i==(lado-1)) && (j== 0)){
            subKey = 92;
        }
        if((i==(lado-1)) && (j==(lado-1))){
            subKey = 93;
        }
    }
    return subKey;
}

void MapDescriptor::assingUnits(int i, int j, int subKey, int &techLevelCounter) {
    for (unsigned int k = 0; k <this->subDescriptors[subKey].units.size() ; ++k) {
        unit unitK =this->subDescriptors[subKey].units[k];
        if(!this->techLevels.empty()) {
            if ((unitK.id == CODE_VF) || (unitK.id == CODE_RF)) {
                unitK.techLevel = this->techLevels[techLevelCounter];
                techLevelCounter++;
            }
        }
        unitK.posX = unitK.posX + ((j)*320);
        unitK.posY = unitK.posY + ((i)*320);
        this->unitsInMap.push_back(unitK);
    }

}

void MapDescriptor::assingVehicles() {
    for (int i = 0; i <this->cantVehiculosAbandonados ; ++i) {
        int posX = (obtenerNumeroRandom(1,(this->lado-1)))*320;
        int posY = (obtenerNumeroRandom(1,(this->lado-1)))*320;
        int codeUnit = obtenerNumeroRandom(CODE_JEEP,CODE_MML);
        unit vehicle ={codeUnit,posX,posY,0};
        this->unitsInMap.push_back(vehicle);

    }
}

int MapDescriptor::obtenerCase() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(MIN, MAX);
    int myNumber = dis(gen);
    return myNumber;
}

int MapDescriptor::obtenerNumeroRandom(int rango1, int rango2){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(rango1, rango2);
    int myNumber = dis(gen);
    return myNumber;
}

void MapDescriptor::show(std::vector<int> &descriptor){
    int limite = lado*SUBDIM;
    for (int i = 0; i <limite ; ++i) {
        for (int j = 0; j <limite ; ++j) {
            std::cout << descriptor[(i*limite)+j] << " ";
        }
        std::cout << "\n";
    }
}

std::vector<unit> MapDescriptor::unitsVector() {
    return this->unitsInMap;
}



subDescriptor MapDescriptor::base(int team) {
    subDescriptor base;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            base.descriptor[i][j] = CODE_ASFALTO;
        }
    }
    for (unsigned int k = 0; k <this->unidadesIniciales.size() ; ++k) {
        int posX = 16;
        int posY = k*32;
        unit unit = {this->unidadesIniciales[k],posX,posY,team};
        base.units.push_back(unit);
    }
    unit fort={FORT_CODE,64,64,team};
    base.units.push_back(fort);

    return base;
}


subDescriptor MapDescriptor::random1(int tile1, int tile2) {
    subDescriptor randomSub;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub.descriptor[i][j] = tile1;
        }
    }
    randomSub.descriptor[4][1] = tile2;
    randomSub.descriptor[4][2] = tile2;
    randomSub.descriptor[4][3] = tile2;
    randomSub.descriptor[4][4] = tile2;
    randomSub.descriptor[4][5] = tile2;
    randomSub.descriptor[4][6] = tile2;
    randomSub.descriptor[4][7] = tile2;
    randomSub.descriptor[4][8] = tile2;
    randomSub.descriptor[1][4] = tile2;
    randomSub.descriptor[2][4] = tile2;
    randomSub.descriptor[3][4] = tile2;
    randomSub.descriptor[5][4] = tile2;
    randomSub.descriptor[6][4] = tile2;
    randomSub.descriptor[7][4] = tile2;
    randomSub.descriptor[8][4] = tile2;
    unit vehiclef1 ={CODE_VF,32,32,0};
    unit flagVF1 ={CODE_FLAG,32,224,0};
    randomSub.units.push_back(flagVF1);
    randomSub.units.push_back(vehiclef1);
    return randomSub;

}

subDescriptor MapDescriptor::random2(int tile1, int tile2) {
    subDescriptor randomSub2;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub2.descriptor[i][j] = tile1;
        }
    }
    randomSub2.descriptor[4][1] = tile2;
    randomSub2.descriptor[4][2] = tile2;
    randomSub2.descriptor[4][3] = tile2;
    randomSub2.descriptor[4][4] = tile2;
    randomSub2.descriptor[4][5] = tile2;
    randomSub2.descriptor[4][6] = tile2;
    randomSub2.descriptor[4][7] = tile2;
    randomSub2.descriptor[4][8] = tile2;
    randomSub2.descriptor[1][4] = tile2;
    randomSub2.descriptor[2][4] = tile2;
    randomSub2.descriptor[3][4] = tile2;
    randomSub2.descriptor[5][4] = tile2;
    randomSub2.descriptor[6][4] = tile2;
    randomSub2.descriptor[7][4] = tile2;
    randomSub2.descriptor[8][4] = tile2;
    unit robotF2 ={CODE_RF,32,32,0};
    unit flagRF2 ={CODE_FLAG,32,224,0};
    randomSub2.units.push_back(flagRF2);
    randomSub2.units.push_back(robotF2);
    return randomSub2;
}

subDescriptor MapDescriptor::random3(int tile1, int tile2) {
    subDescriptor randomSub3;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub3.descriptor[i][j] = tile1;
        }
    }
    for (int k = 3; k <7 ; ++k) {
        for (int i = 3; i < 7; ++i) {
            randomSub3.descriptor[k][i] = tile2;
        }
    }
    unit iceB1 ={CODE_ICEB,96,96,0};
    randomSub3.units.push_back(iceB1);
    unit iceB2 ={CODE_ICEB,96,128,0};
    randomSub3.units.push_back(iceB2);
    unit iceB3 ={CODE_ICEB,96,160,0};
    randomSub3.units.push_back(iceB3);
    unit iceB4 ={CODE_ICEB,96,192,0};
    randomSub3.units.push_back(iceB4);
    unit iceB5 ={CODE_ICEB,96,224,0};
    randomSub3.units.push_back(iceB5);
    unit iceB6 ={CODE_ICEB,128,96,0};
    randomSub3.units.push_back(iceB6);
    unit iceB7 ={CODE_ICEB,160,96,0};
    randomSub3.units.push_back(iceB7);
    unit iceB8 ={CODE_ICEB,192,96,0};
    randomSub3.units.push_back(iceB8);
    unit iceB9 ={CODE_ICEB,224,96,0};
    randomSub3.units.push_back(iceB9);
    unit iceB10 ={CODE_ICEB,224,128,0};
    randomSub3.units.push_back(iceB10);
    unit iceB11 ={CODE_ICEB,224,160,0};
    randomSub3.units.push_back(iceB11);
    unit iceB12 ={CODE_ICEB,224,192,0};
    randomSub3.units.push_back(iceB12);
    unit iceB13 ={CODE_ICEB,224,224,0};
    randomSub3.units.push_back(iceB13);
    unit iceB14 ={CODE_ICEB,128,224,0};
    randomSub3.units.push_back(iceB14);
    unit iceB15 ={CODE_ICEB,160,224,0};
    randomSub3.units.push_back(iceB15);
    unit iceB16 ={CODE_ICEB,192,224,0};
    randomSub3.units.push_back(iceB16);
    unit flagVF2 = {CODE_FLAG,160,160,0};
    randomSub3.units.push_back(flagVF2);
    unit vehicleF2 ={CODE_VF,0,0,0};
    randomSub3.units.push_back(vehicleF2);
    return  randomSub3;
}

subDescriptor MapDescriptor::random4(int tile1, int tile2) {
    subDescriptor randomSub4;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub4.descriptor[i][j] = tile1;
        }
    }
    for (int k = 3; k <7 ; ++k) {
        for (int i = 3; i < 7; ++i) {
            randomSub4.descriptor[k][i] = tile2;
        }
    }
    unit rockB1 ={CODE_ROCK,96,96,0};
    randomSub4.units.push_back(rockB1);
    unit rockB2 ={CODE_ROCK,96,128,0};
    randomSub4.units.push_back(rockB2);
    unit rockB3 ={CODE_ROCK,96,160,0};
    randomSub4.units.push_back(rockB3);
    unit rockB4 ={CODE_ROCK,96,192,0};
    randomSub4.units.push_back(rockB4);
    unit rockB5 ={CODE_ROCK,96,224,0};
    randomSub4.units.push_back(rockB5);
    unit rockB6 ={CODE_ROCK,128,96,0};
    randomSub4.units.push_back(rockB6);
    unit rockB7 ={CODE_ROCK,160,96,0};
    randomSub4.units.push_back(rockB7);
    unit rockB8 ={CODE_ROCK,192,96,0};
    randomSub4.units.push_back(rockB8);
    unit rockB9 ={CODE_ROCK,224,96,0};
    randomSub4.units.push_back(rockB9);
    unit rockB10 ={CODE_ROCK,224,128,0};
    randomSub4.units.push_back(rockB10);
    unit rockB11 ={CODE_ROCK,224,160,0};
    randomSub4.units.push_back(rockB11);
    unit rockB12 ={CODE_ROCK,224,192,0};
    randomSub4.units.push_back(rockB12);
    unit rockB13 ={CODE_ROCK,224,224,0};
    randomSub4.units.push_back(rockB13);
    unit rockB14 ={CODE_ROCK,128,224,0};
    randomSub4.units.push_back(rockB14);
    unit rockB15 ={CODE_ROCK,160,224,0};
    randomSub4.units.push_back(rockB15);
    unit rockB16 ={CODE_ROCK,192,224,0};
    randomSub4.units.push_back(rockB16);
    unit flagRF3 = {CODE_FLAG,160,160,0};
    randomSub4.units.push_back(flagRF3);
    unit robotF3 ={CODE_RF,0,0,0};
    randomSub4.units.push_back(robotF3);
    return randomSub4;
}

subDescriptor MapDescriptor::random5(int tile1, int tile2) {
    subDescriptor randomSub5;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub5.descriptor[i][j] = tile1;
        }
    }
    for (int i = 2; i < 9 ; ++i) {
        for (int j = 2; j <9 ; ++j) {
            randomSub5.descriptor[i][j] = tile2;
        }
    }
    for (int i = 3; i < 8 ; ++i) {
        for (int j = 3; j <8 ; ++j) {
            randomSub5.descriptor[i][j] = tile1;
        }
    }
    unit flagRF4 = {CODE_FLAG,224,160,0};
    randomSub5.units.push_back(flagRF4);
    unit robotF4 ={CODE_RF,96,96,0};
    randomSub5.units.push_back(robotF4);
    unit bridgeH = {CODE_BRIDGE,48,224,0};
    randomSub5.units.push_back(bridgeH);
    return randomSub5;
}

subDescriptor MapDescriptor::random6(int tile1, int tile2) {
    subDescriptor randomSub6;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub6.descriptor[i][j] = tile1;
        }
    }
    for (int i = 2; i < 9 ; ++i) {
        for (int j = 2; j <9 ; ++j) {
            randomSub6.descriptor[i][j] = tile2;
        }
    }
    for (int i = 3; i < 8 ; ++i) {
        for (int j = 3; j <8 ; ++j) {
            randomSub6.descriptor[i][j] = tile1;
        }
    }
    unit flagRF5 = {CODE_FLAG,224,160,0};
    randomSub6.units.push_back(flagRF5);
    unit vehicleF5 ={CODE_VF,96,96,0};
    randomSub6.units.push_back(vehicleF5);
    unit bridgeH2 = {CODE_BRIDGE,48,224,0};
    randomSub6.units.push_back(bridgeH2);
    return randomSub6;
}

subDescriptor MapDescriptor::random7(int tile1, int tile2) {
    subDescriptor randomSub7;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub7.descriptor[i][j] = tile1;
        }
    }
    for (int i = 0; i < SUBDIM ; ++i) {
        randomSub7.descriptor[1][i] = tile2;
        randomSub7.descriptor[8][i] = tile2;
    }
    unit flagRF6 = {CODE_FLAG,256,160,0};
    randomSub7.units.push_back(flagRF6);
    unit vehicleF6 ={CODE_VF,96,96,0};
    randomSub7.units.push_back(vehicleF6);
    unit bridgeV1 = {CODE_BRIDGEV,32,32,0};
    randomSub7.units.push_back(bridgeV1);
    unit bridgeV2 = {CODE_BRIDGEV,32,256,0};
    randomSub7.units.push_back(bridgeV2);
    return randomSub7;
}

subDescriptor MapDescriptor::random8(int tile1, int tile2) {
    subDescriptor randomSub8;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub8.descriptor[i][j] = tile1;
        }
    }
    for (int i = 0; i < SUBDIM ; ++i) {
        randomSub8.descriptor[1][i] = tile2;
        randomSub8.descriptor[8][i] = tile2;
    }
    unit flagRF7 = {CODE_FLAG,256,160,0};
    randomSub8.units.push_back(flagRF7);
    unit robotF7 ={CODE_RF,96,96,0};
    randomSub8.units.push_back(robotF7);
    unit bridgeV3 = {CODE_BRIDGEV,32,32,0};
    randomSub8.units.push_back(bridgeV3);
    unit bridgeV4 = {CODE_BRIDGEV,32,256,0};
    randomSub8.units.push_back(bridgeV4);
    return randomSub8;
}


subDescriptor MapDescriptor::random1_terrain(int tile1, int tile2) {
    subDescriptor randomSub;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub.descriptor[i][j] = tile1;
        }
    }
    randomSub.descriptor[4][1] = tile2;
    randomSub.descriptor[4][2] = tile2;
    randomSub.descriptor[4][3] = tile2;
    randomSub.descriptor[4][4] = tile2;
    randomSub.descriptor[4][5] = tile2;
    randomSub.descriptor[4][6] = tile2;
    randomSub.descriptor[4][7] = tile2;
    randomSub.descriptor[4][8] = tile2;
    randomSub.descriptor[1][4] = tile2;
    randomSub.descriptor[2][4] = tile2;
    randomSub.descriptor[3][4] = tile2;
    randomSub.descriptor[5][4] = tile2;
    randomSub.descriptor[6][4] = tile2;
    randomSub.descriptor[7][4] = tile2;
    randomSub.descriptor[8][4] = tile2;
    return randomSub;

}

subDescriptor MapDescriptor::random2_terrain(int tile1, int tile2) {
    subDescriptor randomSub2;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub2.descriptor[i][j] = tile1;
        }
    }
    randomSub2.descriptor[4][1] = tile2;
    randomSub2.descriptor[4][2] = tile2;
    randomSub2.descriptor[4][3] = tile2;
    randomSub2.descriptor[4][4] = tile2;
    randomSub2.descriptor[4][5] = tile2;
    randomSub2.descriptor[4][6] = tile2;
    randomSub2.descriptor[4][7] = tile2;
    randomSub2.descriptor[4][8] = tile2;
    randomSub2.descriptor[1][4] = tile2;
    randomSub2.descriptor[2][4] = tile2;
    randomSub2.descriptor[3][4] = tile2;
    randomSub2.descriptor[5][4] = tile2;
    randomSub2.descriptor[6][4] = tile2;
    randomSub2.descriptor[7][4] = tile2;
    randomSub2.descriptor[8][4] = tile2;
    return randomSub2;
}

subDescriptor MapDescriptor::random3_terrain(int tile1, int tile2) {
    subDescriptor randomSub3;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub3.descriptor[i][j] = tile1;
        }
    }
    for (int k = 3; k <7 ; ++k) {
        for (int i = 3; i < 7; ++i) {
            randomSub3.descriptor[k][i] = tile2;
        }
    }
    unit iceB1 ={CODE_ICEB,96,96,0};
    randomSub3.units.push_back(iceB1);
    unit iceB2 ={CODE_ICEB,96,128,0};
    randomSub3.units.push_back(iceB2);
    unit iceB3 ={CODE_ICEB,96,160,0};
    randomSub3.units.push_back(iceB3);
    unit iceB4 ={CODE_ICEB,96,192,0};
    randomSub3.units.push_back(iceB4);
    unit iceB5 ={CODE_ICEB,96,224,0};
    randomSub3.units.push_back(iceB5);
    unit iceB6 ={CODE_ICEB,128,96,0};
    randomSub3.units.push_back(iceB6);
    unit iceB7 ={CODE_ICEB,160,96,0};
    randomSub3.units.push_back(iceB7);
    unit iceB8 ={CODE_ICEB,192,96,0};
    randomSub3.units.push_back(iceB8);
    unit iceB9 ={CODE_ICEB,224,96,0};
    randomSub3.units.push_back(iceB9);
    unit iceB10 ={CODE_ICEB,224,128,0};
    randomSub3.units.push_back(iceB10);
    unit iceB11 ={CODE_ICEB,224,160,0};
    randomSub3.units.push_back(iceB11);
    unit iceB12 ={CODE_ICEB,224,192,0};
    randomSub3.units.push_back(iceB12);
    unit iceB13 ={CODE_ICEB,224,224,0};
    randomSub3.units.push_back(iceB13);
    unit iceB14 ={CODE_ICEB,128,224,0};
    randomSub3.units.push_back(iceB14);
    unit iceB15 ={CODE_ICEB,160,224,0};
    randomSub3.units.push_back(iceB15);
    unit iceB16 ={CODE_ICEB,192,224,0};
    randomSub3.units.push_back(iceB16);
    return  randomSub3;
}

subDescriptor MapDescriptor::random4_terrain(int tile1, int tile2) {
    subDescriptor randomSub4;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub4.descriptor[i][j] = tile1;
        }
    }
    for (int k = 3; k <7 ; ++k) {
        for (int i = 3; i < 7; ++i) {
            randomSub4.descriptor[k][i] = tile2;
        }
    }
    unit rockB1 ={CODE_ROCK,96,96,0};
    randomSub4.units.push_back(rockB1);
    unit rockB2 ={CODE_ROCK,96,128,0};
    randomSub4.units.push_back(rockB2);
    unit rockB3 ={CODE_ROCK,96,160,0};
    randomSub4.units.push_back(rockB3);
    unit rockB4 ={CODE_ROCK,96,192,0};
    randomSub4.units.push_back(rockB4);
    unit rockB5 ={CODE_ROCK,96,224,0};
    randomSub4.units.push_back(rockB5);
    unit rockB6 ={CODE_ROCK,128,96,0};
    randomSub4.units.push_back(rockB6);
    unit rockB7 ={CODE_ROCK,160,96,0};
    randomSub4.units.push_back(rockB7);
    unit rockB8 ={CODE_ROCK,192,96,0};
    randomSub4.units.push_back(rockB8);
    unit rockB9 ={CODE_ROCK,224,96,0};
    randomSub4.units.push_back(rockB9);
    unit rockB10 ={CODE_ROCK,224,128,0};
    randomSub4.units.push_back(rockB10);
    unit rockB11 ={CODE_ROCK,224,160,0};
    randomSub4.units.push_back(rockB11);
    unit rockB12 ={CODE_ROCK,224,192,0};
    randomSub4.units.push_back(rockB12);
    unit rockB13 ={CODE_ROCK,224,224,0};
    randomSub4.units.push_back(rockB13);
    unit rockB14 ={CODE_ROCK,128,224,0};
    randomSub4.units.push_back(rockB14);
    unit rockB15 ={CODE_ROCK,160,224,0};
    randomSub4.units.push_back(rockB15);
    unit rockB16 ={CODE_ROCK,192,224,0};
    randomSub4.units.push_back(rockB16);
    return randomSub4;
}

subDescriptor MapDescriptor::random5_terrain(int tile1, int tile2) {
    subDescriptor randomSub5;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub5.descriptor[i][j] = tile1;
        }
    }
    for (int i = 2; i < 9 ; ++i) {
        for (int j = 2; j <9 ; ++j) {
            randomSub5.descriptor[i][j] = tile2;
        }
    }
    for (int i = 3; i < 8 ; ++i) {
        for (int j = 3; j <8 ; ++j) {
            randomSub5.descriptor[i][j] = tile1;
        }
    }
    unit bridgeH = {CODE_BRIDGE,48,224,0};
    randomSub5.units.push_back(bridgeH);
    return randomSub5;
}

subDescriptor MapDescriptor::random6_terrain(int tile1, int tile2) {
    subDescriptor randomSub6;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub6.descriptor[i][j] = tile1;
        }
    }
    for (int i = 2; i < 9 ; ++i) {
        for (int j = 2; j <9 ; ++j) {
            randomSub6.descriptor[i][j] = tile2;
        }
    }
    for (int i = 3; i < 8 ; ++i) {
        for (int j = 3; j <8 ; ++j) {
            randomSub6.descriptor[i][j] = tile1;
        }
    }
    unit bridgeH2 = {CODE_BRIDGE,48,224,0};
    randomSub6.units.push_back(bridgeH2);
    return randomSub6;
}

subDescriptor MapDescriptor::random7_terrain(int tile1, int tile2) {
    subDescriptor randomSub7;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub7.descriptor[i][j] = tile1;
        }
    }
    for (int i = 0; i < SUBDIM ; ++i) {
        randomSub7.descriptor[1][i] = tile2;
        randomSub7.descriptor[8][i] = tile2;
    }
    unit bridgeV1 = {CODE_BRIDGEV,32,32,0};
    randomSub7.units.push_back(bridgeV1);
    unit bridgeV2 = {CODE_BRIDGEV,32,256,0};
    randomSub7.units.push_back(bridgeV2);
    return randomSub7;
}

subDescriptor MapDescriptor::random8_terrain(int tile1, int tile2) {
    subDescriptor randomSub8;
    for (int i = 0; i < SUBDIM ; ++i) {
        for (int j = 0; j <SUBDIM ; ++j) {
            randomSub8.descriptor[i][j] = tile1;
        }
    }
    for (int i = 0; i < SUBDIM ; ++i) {
        randomSub8.descriptor[1][i] = tile2;
        randomSub8.descriptor[8][i] = tile2;
    }
    unit bridgeV3 = {CODE_BRIDGEV,32,32,0};
    randomSub8.units.push_back(bridgeV3);
    unit bridgeV4 = {CODE_BRIDGEV,32,256,0};
    randomSub8.units.push_back(bridgeV4);
    return randomSub8;
}
