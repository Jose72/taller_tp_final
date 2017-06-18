#include "territory.h"

territory::territory(unit *f, std::vector<unit*> &facts): flag(f), factories(facts){}


//chequea si la bandera es del territorio
bool territory::flagBelongToTerritory(unit *f){
	return (flag == f);
}


//cambia el owner de las fabricas
//se asume que el flag ya cambio de owner
void territory::changeOwnership(){
	int n_owner = flag->getOwner();
	for (auto it = factories.begin(); it != factories.end(); ++it){
		(*it)->changeOwner(n_owner);
	}
}