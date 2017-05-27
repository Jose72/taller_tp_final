#ifndef CREATEBEHAVIOUR_H
#define CREATEBEHAVIOUR_H

#include "behaviour.h"
#include "armament.h"
#include "unit.h"
#include <vector>


//esta dentro de unit
//tiene un contador con el tiempo restante hasta que se fabrique la unidad
//cuando se actualizan las unidades ese tiempo se reduce (el time slice utilizado)
//alli hay que tomar el codigo de unidad y crearla en el juego
class createBehaviour: public behaviour {
	private:
		int time_count; //en segundos, contador de tiempo, cuando llega a 0 crea la unidad
		int unit_code; //codigo de la unidad que se esta fabricando 
		int tech_level;
	public:
		createBehaviour(int unit_c);
		int actualize(int t);
		void create(int unit_c);
		int getUnitCode();
};

#endif