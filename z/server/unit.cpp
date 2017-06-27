#include "unit.h"
#include <iostream>
#include "math.h"
#include <vector>


#define INVALID_POS -200

unit::unit(int unit_id, int class_id, int height, int width, int owner, int x, int y, 
int health, int state, int blocking, int speed, int a_range, int base_damage, bool explosive, 
int base_time, int unit_to_c, int tech_level): unit_id(unit_id),   
class_id(class_id), height(height), width(width), owner(owner), x(x), y(y), b_health(health), 
health(health), state(state), blocking(blocking), dest_x(x), dest_y(y) ,speed(speed), 
driver(nullptr), target(nullptr), attack_range(a_range), 
base_damage(base_damage), explosive_damage(explosive), auto_attack(false), base_time(base_time), 
countdown(base_time), unit_code_to_create(unit_to_c), 
tech_level(tech_level) {}



void unit::setPos(double p_x, double p_y){
	x = p_x;
	y = p_y;
}


bool unit::isMoving(){
	
	if ((x != dest_x || y != dest_y)) return true;
	return false;
};

int unit::getUnitId(){
	return unit_id;
}

int unit::getClassId(){
	return class_id;
}

int unit::getX(){
	return round(x);
}

int unit::getY(){
	return round(y);
}

int unit::getDestX(){
	return dest_x;
}

int unit::getDestY(){
	return dest_y;
}

double unit::getX_D(){
	return x;
}
		
double unit::getY_D(){
	return y;
}

int unit::getHealth(){
	return health;
}


void unit::printPos(){
	std::cout << "unit--------" << std::endl;
	std::cout << "x_pos: " << x << std::endl;
	std::cout << "y_pos: " << y << std::endl;
	std::cout << "health: " << health << std::endl;
}

int unit::getSpeed(){
	return speed;
}

double unit::getRelativeDamage(){
	if (b_health != 0){
		return ((b_health - health) / (double) b_health);
	}
	return 1;
}

//////////////////////////////////////////////////
////// EVENT METHODS /////////////////////////////
//////////////////////////////////////////////////

void unit::move(int d_x, int d_y){
	dest_x = d_x;
	dest_y = d_y;
	auto_attack = false;
	state = MOVING;
	//no sigo mas a mi target
	if (target) {
		target->removeFollower(this);
		target = nullptr;
	}
}

void unit::attack(unit *u){
	if (u) {
		auto_attack = false;
		target = u;
		u->setFollower(this);
		if (this->targetIsInRange()){
			this->changeState(ATTACKING);
		} else {
			this->moveToTarget();
		}
	} 
}

void unit::follow(unit *u){
	if (u) {
		auto_attack = false;
		target = u;
		u->setFollower(this);
		if (this->targetIsInRange()){
			this->changeState(STANDING);
		} else {
			this->moveToTarget();
		}
	}
}

void unit::drive(unit *vehicle){
	//si tenia target le digo que no lo sigo y targetteo vehiculo
	if (target) target->removeFollower(this);
	target = vehicle;
	target->setFollower(this);
	auto_attack = false;
	//si estoy en rango lo conduzco, sino me pongo en moving
	if (this->targetIsInRange() && this->canDriveTarget()){
		this->driveTarget();
		
		
		//setear una pos invalida
		this->x = INVALID_POS;
		this->y = INVALID_POS;
		
		
	} else {
		this->moveToTarget();
	}
}


void unit::create(int u_id, int time){
	if (class_id != BUILDING) return;
	if (unit_code_to_create != u_id){
		this->unit_code_to_create = u_id;
		this->base_time = time;
		this->resetTimer();
	}
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////


void unit::stop(){
	dest_x = x;
	dest_y = y;
}

bool unit::isInRange(unit &u){
	if (sqrt(pow((this->getCenterX_D() - u.getCenterX_D()),2) + 
	pow((this->getCenterY_D() - u.getCenterY_D()),2)) <= (this->attack_range + 
	this->getRadius() + u.getRadius())) {
		return true;
	}
	return false;
}

int unit::takeDamage(int dam, bool explosive){
	if ((class_id == BUILDING || class_id == BRIDGE_C || class_id == BLOCK) && !explosive) return 0;
	if (health - dam <= 0) {
		health = 0;
		state = DEAD;
		this->stopFollowers();
	} else {
		health = health - dam;
	}
	return DAMAGE_TAKEN;
}

void unit::setAttack(unit *u){
	if (u->owner != this->owner){
		target = u;
	}
	
}

void unit::setDestiny(int x, int y){
	dest_x = x;
	dest_y = y;
}

int unit::attackRange(){
	return attack_range;
}

double unit::getDamage(){
	return base_damage;
}

unit* unit::getTarget(){
	return target;
}

void unit::printPosDest(){
	std::cout << "x: " << x << " d_x: " << dest_x << std::endl;
	std::cout << "y: " << y << " d_y: " << dest_y << std::endl;
}

bool unit::isEnemy(unit *u){
	//pendiente: chequear si el owner es mageMap 
	//(en el caso de que la unidad sea una piedra u otro objeto destruible)

	if (!u || u->owner == 0 || u->class_id == FLAG) return false;
	if (this->owner != u->owner) {
		//if (this->sameTeam(&u)) return false;
		return true;
	}
	return false;
}


int unit::getOwner(){
	return owner;
}


//chequeo el estado tambien porque 
//puedo haberlo seteado sin que la vida sea 0
bool unit::isAlive(){
	if (health > 0 && state != DEAD) return true;
	return false;
}


//countdown me dice cuando puedo atacar (cuando esta en 0)
//hay "espera" por la frecuencia de disparo
//
bool unit::canAttack(){
	return (countdown <= 0);
}

//resto el tiempo del time slice al countdown
//el tiempo en milisegundos
void unit::actualizeTimer(int time){
	if (countdown - time < 0) {
		countdown = 0;
		return;
	}
	countdown = countdown - time;
}

//reseteo el countdown si acabo de disparar
void unit::resetTimer(){
	countdown = base_time;
}

int unit::unitToCreate(){
	return unit_code_to_create;
}

void unit::changeState(int s){
	state = s;
}

bool unit::targetIsInRange(){
	if (target) {
		return this->isInRange(*target);
		//if (sqrt(pow((x - target->x),2) + pow((y - target->y),2)) <= this->attack_range) {
		//return true;
		//}
	}
	return false;
}


void unit::moveToCenterTarget(){
	if (target){
		this->dest_x = target->getCenterX();
		this->dest_y = target->getCenterY();
		state = MOVING;
	} else {
		state = STANDING;
	}
}


//si tengo taget lo pongo como destino
//sino me quedo quieto
void unit::moveToTarget(){
	if (target){
		this->dest_x = target->getCenterX();
		this->dest_y = target->getCenterY();
		state = MOVING;
	} else {
		state = STANDING;
	}
}

bool unit::targetIsEnemy(){
	if (this->isEnemy(target)) return true;
	return false;
}

int unit::getState(){
	return state;
}

//seteo a los que me estan siguiendo
//para cuando muera les aviso
void unit::setFollower(unit *u){
	if (this->isFollowedBy(u)) return; //si ya lo tengo no hago nada
	followers.push_back(u);
}


//si estaba targeteando a la unidad, no lo hago mas
void unit::removeTarget(unit *u){
	if (target == u){
		target = nullptr;
	}
}

bool unit::isDead(){
	if (state == DEAD) return true;
	return false;
}

//true si u es uno de mis followers
bool unit::isFollowedBy(unit *u){
	for (auto it = followers.begin(); it != followers.end(); ++it){
		if ((*it) == u){
			return true;
		}
	}
	return false;
}

//remuevo de mi lista de followers
void unit::removeFollower(unit* u){
	for (auto it = followers.begin(); it != followers.end(); ++it){
		if ((*it) == u){
			followers.erase(it);
			return;
		}
	}
}

//le digo a mis followers que no me sigan, que seteen su target a null
void unit::stopFollowers(){
	for (auto it = followers.begin(); it != followers.end(); ++it){
		(*it)->removeTarget(this);
	}
	//limpio el vector
	followers.clear();
}

bool unit::canCreate(){
	return (countdown == 0);
}

//setea target, pone en autoatacke y pasa al ataque
void unit::setAutoAttack(unit *u){
	target = u;
	u->setFollower(this);
	auto_attack = true;
	state = ATTACKING;
}

bool unit::autoAttackEnabled(){
	return auto_attack;
}

void unit::setTarget(unit *u){
	target = u;
}

bool unit::sameOwner(unit *u){
	if (this->owner == u->owner) return true;
	return false;
}

bool unit::sameOwnerAsTarget(){
	if (this->owner == target->owner) return true;
	return false;
}

bool unit::timerIsZero(){
	if (countdown == 0) return true;
	return false;
}


void unit::changeOwnerForTargetOwner(){
	owner = target->owner;
}

int unit::getTargetOwner(){
	if (target) return target->getOwner();
	return -1;
}

int unit::getTechLvl(){
	return tech_level;
}


bool unit::canDriveTarget(){
	//mismo dueño  
	//target es vehiculo
	//el vehiculo no tiene conductor
	//unidad es robot
	if (target->owner == 0 && 
	target->class_id == VEHICLE && !target->driver
	 && this->class_id == ROBOT) return true;
	return false;
	
}

void unit::driveTarget(){
	this->stopFollowers();
	target->driver = this;
	//target->owner = this->owner;
	//std::cout << "new owner: " << target->owner << std::endl;
	state = DRIVING;
}

bool unit::isDriving(){
	return (state == DRIVING);
}

bool unit::isExplosiveDamage(){
	return explosive_damage;
}


//el tiempo se descuenta del timer
//cuantos mas territorios tenga o menos daño realtivo
//mas tiempo se descuenta -> mas rapido se crea la unidad
void unit::updateCreationTimer(int time, int t_count){
	if (countdown - time < 0){
		countdown = 0;
	} else {
		if (t_count == 0){
			std::cout << "BADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD" << std::endl;
		}
		countdown -=(time * t_count) * (sqrt(1-(this->getRelativeDamage())));
	}
}

void unit::setTechLvl(int tl){
	tech_level = tl;
}

void unit::setFlagTarget(unit *u){
	target = u;
	u->setFollower(this);
}

void unit::releaseDriver(){
	if (driver){
		driver->x = this->x;
		driver->y = this->y;
		driver->target = nullptr;
		driver->state = STANDING;
	}
}

int unit::getWidth(){
	return width;
}

int unit::getHeight(){
	return height;
}

int unit::getCenterX(){
	return x + (width / 2);
}

int unit::getCenterY(){
	return y + (height / 2);
}
double unit::getCenterX_D(){
	return x + (width / 2);
}

double unit::getCenterY_D(){
	return y + (height / 2);
}

//tomo el radio mas pequeño
double unit::getRadius(){
	if (height < width){
		return (height / 2);
	}
	return (width / 2);
}

int unit::getBlockingType(){
	return blocking;
}

void unit::changeOwner(int o){
	owner = o;
}

unit* unit::getDriver(){
	return driver;
}

//una unidad atacable es un enemigo
//o una unidad con owner 0 (que no sea un vehiculo)
//tampoco puede ser una bala
bool unit::isAttackable(unit *u){
	return ((this->isEnemy(u) || 
	(u->owner == 0 && u->class_id != VEHICLE)) && 
	(u->class_id != BULLET));
	
}

bool unit::targetIsAttackable(){
	if (target){
		return this->isAttackable(target);
	}
	return false;
}


//cuanto falta para que se complete la unidad que se esta creando
//devuele un porcentage del 0 al 100
int unit::getTimeToCompletion(){
	if (base_time != 0){
		return round((countdown/base_time)*100);
	}
	return 0;
}


//si la unidad recibida como parametro esta "encima"
bool unit::hasOnTop(unit *u){
	bool dx = ((this->x) < (u->x) &&  (u->x) < (this->x + this->width));
	bool dy = ((this->y) < (u->y) && (u->y) < (this->y + this->height));
	return (dx && dy);
}


//setea a la unidad como conductor del vehiculo instantaneamente
//para inicializar los vehiculos cuando se crean
void unit::instantDrive(unit *vehicle){
	if (target) target->removeFollower(this);
	target = vehicle;
	this->driveTarget();
	//setear una pos invalida
	this->x = -200;
	this->y = -200;
}


bool unit::timerComplete(){
	return (countdown <= 0);
}

void unit::resetAttackTimer(){
	countdown =+ base_time;
}

void unit::actualizeCaptureTimer(int time){
	if (countdown - time < 0){
		countdown = 0;
	} else {
		countdown -= time;
	}
}