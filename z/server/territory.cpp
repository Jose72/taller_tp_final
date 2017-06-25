#include "territory.h"

territory::territory(unit *f, unit *factory): flag(f), factory(factory){}


//chequea si la bandera es del territorio
bool territory::flagBelongToTerritory(unit *f){
	return (flag == f);
}


//cambia el owner de las fabricas
//si el flag ya cambio de owner
//si el nuevo owner es distinto de 0 (es un team) pasa a CREATING y reseteo el timer
void territory::changeOwnership(){
	int n_owner = flag->getOwner();
	if(n_owner != factory->getOwner()){
		factory->changeOwner(n_owner);
		if (factory->getOwner() != 0){
			factory->changeState(CREATING);
			factory->resetTimer();
		}
	}

}