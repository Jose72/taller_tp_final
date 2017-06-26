#include <map>
#include <vector>

#ifndef GENMAP_MAPDESCRIPTOR_H
#define GENMAP_MAPDESCRIPTtypedef OR_H


struct unit{
    int id;
    int posX;
    int posY;
    int owner;
    int techLevel;
};

struct subDescriptor{
    int descriptor[10][10];
    std::vector<unit> units;
};


class MapDescriptor {
private:
    int lado;
    int cantEquipos;
    int cantTerritorios;
    std::vector<int> &techLevels;
    int cantVehiculosAbandonados;
    std::vector<int> &unidadesIniciales;
    int setTiles;
    std::vector<unit> unitsInMap;
    std::map<int,subDescriptor> subDescriptors;
    int techLevelFuerte;



public:

    MapDescriptor(int lado,
                  int equipos,
                  int cantTerritorios,
                  std::vector<int> &techLevels,
                  int vehiculosAbandonados,
                  std::vector<int> &unidadesIniciales,
                  int setTiles,
                  int techLevelFuerte);
    std::vector<int> generate();
    void show(std::vector<int> &descriptor);
    int  obtenerCase();
    void createDescriptor(int equipos, int setTiles);
    std::vector<unit> unitsVector();
    void assingUnits(int i, int j, int subKey, int &techLevelCounter);
    int obtenerSubKey(int i, int j, int subKey);
    int obtenerNumeroRandom(int rango1, int rango2);
    void assingVehicles();


private:
    std::vector<int> randomize2();
    subDescriptor base(int team);
    subDescriptor random1(int tile1, int tile2);
    subDescriptor random2(int tile1, int tile2);
    subDescriptor random3(int tile1, int tile2);
    subDescriptor random4(int tile1, int tile2);
    subDescriptor random5(int tile1, int tile2);
    subDescriptor random6(int tile1, int tile2);
    subDescriptor random7(int tile1, int tile2);
    subDescriptor random8(int tile1, int tile2);

    subDescriptor random1_terrain(int tile1, int tile2);
    subDescriptor random2_terrain(int tile1, int tile2);
    subDescriptor random3_terrain(int tile1, int tile2);
    subDescriptor random4_terrain(int tile1, int tile2);
    subDescriptor random5_terrain(int tile1, int tile2);
    subDescriptor random6_terrain(int tile1, int tile2);
    subDescriptor random7_terrain(int tile1, int tile2);
    subDescriptor random8_terrain(int tile1, int tile2);

};


#endif //GENMAP_MAPDESCRIPTOR_H
