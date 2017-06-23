#include <iostream>
#include <vector>
#include <fstream>
#include "JsonHandler.h"
#define PIEZAP 32
#define PIEZAM 10


int main() {
    std::string mapName;
    int cantDeEquipos;
    int tamanioLado;
    int cantTerritorios;
    int cantMaximaTerritorios;
    std::vector<int> techLevelFabricas;
    int cantVehiculosAbandonados;
    int cantUnidadesIniciales;
    std::vector<int> unitIniciales;
    int setTiles;
    bool datosIngresados = false;
    std::cout<<"Bienvenido al generador de mapas Z:THE GAME"<<"\n";
    std::cout<<"Crear un mapa es muy facil, solo sigue las siguientes instrucciones"<<"\n";
    std::cout<<"Empecemos con el nombre"<<"\n";
    std::cout<<"Ingrese el nombre del mapa" <<"\n";
    std::cin >>mapName;
    std::cout << mapName << ".json y units"<<mapName<<".json seran los nombres de los archivos del mapa"<<"\n";
    std::string mapJsonName = mapName+".json";
    std::string unitsJsonName = "units"+mapName+".json";
    std::cout<<"Los mapas de Z se componen de piezas y son cuadrados"<<"\n";
    std::cout<<"Ingresa cuantas piezas conformaran un lado de tu cuadrado"<<"\n";
    std::cout<<"Quizas te sirva saber que por ejemplo un mapa de lado 3, tiene unas dimension de 960x960"<<"\n";
    std::cout<< "Ingresa la cantidad de piezas de un lado (MAXIMO DE PIEZAS 20)"<<"\n";
    std::cin >> tamanioLado;
    while((tamanioLado<2) ||(tamanioLado>20)){
        std::cout<< "Lado ingresado no soportado, Por favor ingrese un nuevo lado"<<"\n";
        std::cin >> tamanioLado;
    }
    int tamanioMostrar = tamanioLado*PIEZAM*PIEZAP;
    std::cout<<"Se generara un mapa de dimensiones "<<tamanioMostrar <<"x"<<tamanioMostrar <<"\n";

    while(!datosIngresados){
        std::cout<<"Ingrese la cantidad de equipos que soportara el mapa"<<"\n";
        std::cin >> cantDeEquipos;
        switch (cantDeEquipos){
            case 1:
                std::cout<< "No se puede jugar a Z solo"<<"\n";
                break;
            case 2:
                datosIngresados = true;
                std::cout<<"Generando mapa para dos jugadores" <<"\n";
                break;

            case 3:
                datosIngresados = true;
                std::cout<<"Generando mapa para 3 jugadores" <<"\n";
                break;

            case 4:
                datosIngresados = true;
                std::cout<<"Generando mapa para 4 jugadores" << "\n";
                break;

            default:
                std::cout <<"Numero de jugadores no soportado" <<"\n";
        }
    }
    cantMaximaTerritorios = ((tamanioLado*tamanioLado)-cantDeEquipos);

    std::cout<<"Ahora debes ingresar la cantidad de territorios del mapa"<<"\n";
    std::cout<<"Un territorio es una pieza del mapa que contiene un objetivo de interes para los jugadores"<<"\n";
    std::cout<<"Por ser de estas dimensiones el mapa soporta "<<cantMaximaTerritorios<<" territorios" <<"\n";
    std::cout<<"Ingrese la cantidad de territorios del mapa"<<"\n";
    std::cin >>cantTerritorios;
    while((cantTerritorios<0) ||(cantTerritorios>cantMaximaTerritorios)){
        std::cout <<"Cantidad de territorios invalida"<<"\n";
        std::cout<<"Ingrese la cantidad de territorios del mapa"<<"\n";
        std::cin >>cantTerritorios;
    }
    std::cout<<"Habra "<<cantTerritorios<<" en el mapa" <<"\n";
    if(cantTerritorios>0) {
        std::cout << "Ingrese el nivel de tecnologia de cada fabrica (Valores permitidos de 1 a 5)" << "\n";
        for (int i = 0; i < cantTerritorios; ++i) {
            int techLevel;
            std::cin >> techLevel;
            if ((techLevel < 1)) {
                techLevel = 1;
            }
            if (techLevel > 5) {
                techLevel = 5;
            }
            techLevelFabricas.push_back(techLevel);
        }
    }
    std::cout<< "Ahora ingresa la cantidad de vehiculos abandonados que estarian en el mapa"<<"\n";
    std::cout<<"El maximo de vehiculos abandonados es de 10 vehiculos" <<'\n';
    std::cin >> cantVehiculosAbandonados;
    if((cantVehiculosAbandonados<0) || (cantVehiculosAbandonados>10)){
        cantVehiculosAbandonados = 10;
    }
    std::cout<<"Solo faltan 2 pasos. Ingresa las unidades iniciales de cada jugador"<< "\n";
    std::cout<< "Con un limite de 10 unidades, ingresa la cantidad de unidades iniciales de cada jugador"<<"\n";
    std::cin >>cantUnidadesIniciales;
    if((cantUnidadesIniciales<0) || (cantUnidadesIniciales> 10)){
        cantUnidadesIniciales = 10;
    }
    std::cout<<"Ingrese el codigo de unidad correspondiente" <<"\n";
    int code_unit;
    std::cout<<"GRUNT  0"<<"\n";
    std::cout<<"PSYCHO 1"<<"\n";
    std::cout<<"TOUGH  2"<<"\n";
    std::cout<<"PYRO   3"<<"\n";
    std::cout<<"SNIPER 4"<<"\n";
    std::cout<<"LAZER  5"<<"\n";
    std::cout<<"JEEP   6"<<"\n";
    std::cout<<"MEDIUM_TANK 7"<<"\n";
    std::cout<<"LIGHT_TANK  8"<<"\n";
    std::cout<<"HEAVY_TANK  9"<<"\n";
    std::cout<<"MISILE_LAUNCHER 10"<<"\n";

    for (int j = 0; j <cantUnidadesIniciales ; ++j) {
        std::cin >> code_unit;
        while((code_unit<0) ||(code_unit>10)){
            std::cout<<"Codigo incorrecto" <<"\n";
            std::cout<<"Ingrese el codigo de unidad"<<"\n";
            std::cin >>code_unit;
        }
        unitIniciales.push_back(code_unit);
    }

    std::cout<<"Finalmente elige el set de piezas que quieres usar para el mapa"<<"\n";
    std::cout<<"SET VOLCANICO              (ASFALTO-LAVA)        1"<<"\n";
    std::cout<<"SET_PANTANO                (PANTANO-AGUA)        2"<<"\n";
    std::cout<<"SET_CIUDAD                 (CARRETERA-ASFALTO)   3"<<"\n";
    std::cout<<"SET_INVERNAL               (NIEVE-AGUA)          4"<<"\n";
    std::cout<<"SET_HIELOyFUEGO            (NIEVE-LAVA)          5"<<"\n";
    std::cout<<"SET_PANTANO_VOLCANICO      (PANTANO_LAVA)        6"<<"\n";
    std::cout<<"SET_FULL_CARRETERA         (CARRETERA)           7"<<"\n";
    std::cout<<"SET_FULL_NIEVE             (NIEVE)               8"<<"\n";
    std::cout<<"SET_FULL_PANTANO           (PANTANO)             9"<<"\n";
    std::cout<<"SET_FULL_TIERRA            (TIERRA)              10"<<"\n";

    std::cin >>setTiles;
    while((setTiles<1) ||(setTiles>10)){
        std::cout <<"Valor incorrecto, por favor ingrese un valor valido" <<"\n";
        std::cin >>setTiles;
    }
    std::cout <<"Configuracion terminada"<<"\n";


    MapDescriptor mapDescriptor(tamanioLado,cantDeEquipos,cantTerritorios,
                                techLevelFabricas,cantVehiculosAbandonados,
                                unitIniciales,setTiles);

    JsonHandler jsonHandler;

    jsonHandler.toJson(mapDescriptor.generate(), mapJsonName);
    jsonHandler.unitsToJson(mapDescriptor.unitsVector(),unitsJsonName);

    std::cout<<"Mapa y archivos generado, ahora copie los archivos a la carpeta maps dentro de la carpeta server"<<"\n";
    return 0;
}