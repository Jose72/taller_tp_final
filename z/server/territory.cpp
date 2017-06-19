#include "territory.h"

territory::territory(unit *f, std::vector<unit*> &facts): flag(f), factories(facts){}


//chequea si la bandera es del territorio
bool territory::flagBelongToTerritory(unit *f){
	return (flag == f);
}


//cambia el owner de las fabricas
//se asume que el flag ya cambio de owner
//si el nuevo owner es distinto de 0 (es un team) pasa a CREATING
void territory::changeOwnership(){
	int n_owner = flag->getOwner();
	for (auto it = factories.begin(); it != factories.end(); ++it){
		unit *factory = (*it);
		factory->changeOwner(n_owner);
		if (factory->getOwner() != 0){
			factory->changeState(CREATING);
		}
	}
}