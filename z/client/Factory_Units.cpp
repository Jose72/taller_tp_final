#include "Factory_Units.h"

Factory_Units::Factory_Units(SpritesPool &pool):pool(pool) {}

Unit* Factory_Units::createUnit(FlagsUnitType unit,int unit_code, int posx, int posy, int unit_owner) {

    switch ((int) unit){
        case BLUE_GRUNT:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_BLUE_GRUNT),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_GRUNT, unit_owner);
        case GREEN_GRUNT:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_GREEN_GRUNT),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_GRUNT, unit_owner);
        case RED_GRUNT:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_RED_GRUNT),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_GRUNT, unit_owner);

        case YELLOW_GRUNT:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_YELLOW_GRUNT),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_GRUNT, unit_owner);

        case BLUE_TOUGHT:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_TOUGHT_BLUE),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_TOUGHT, unit_owner);
        case GREEN_TOUGHT:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_TOUGHT_GREEN),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_TOUGHT, unit_owner);
        case RED_TOUGHT:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_TOUGHT_RED),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_TOUGHT, unit_owner);

        case YELLOW_TOUGHT:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_TOUGHT_YELLOW),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_TOUGHT, unit_owner);

        case BLUE_PYRO:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_PYRO_BLUE),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_PYRO, unit_owner);
        case GREEN_PYRO:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_PYRO_GREEN),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_PYRO, unit_owner);
        case RED_PYRO:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_PYRO_RED),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_PYRO, unit_owner);

        case YELLOW_PYRO:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_PYRO_YELLOW),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_PYRO, unit_owner);

        case BLUE_PSYCHO:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_PSYCHO_BLUE),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_PSYCHO, unit_owner);
        case GREEN_PSYCHO:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_PSYCHO_GREEN),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_PSYCHO, unit_owner);
        case RED_PSYCHO:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_PSYCHO_RED),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_PSYCHO, unit_owner);

        case YELLOW_PSYCHO:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_PSYCHO_YELLOW),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_PSYCHO, unit_owner);

        case BLUE_SNIPER:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_SNIPER_BLUE),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_SNIPER, unit_owner);
        case GREEN_SNIPER:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_SNIPER_GREEN),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_SNIPER, unit_owner);
        case RED_SNIPER:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_SNIPER_RED),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_SNIPER, unit_owner);

        case YELLOW_SNIPER:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_SNIPER_YELLOW),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_SNIPER, unit_owner);

        case BLUE_LASER:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_LASER_BLUE),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy, DRINKING,BLUE_LASER, unit_owner);
        case GREEN_LASER:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_LASER_GREEN),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_LASER, unit_owner);
        case RED_LASER:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_LASER_RED),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING,GREEN_LASER, unit_owner);

        case YELLOW_LASER:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_LASER_YELLOW),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy,DRINKING,GREEN_LASER, unit_owner);

        case HEAVY_TANK_EMPTY:
            return new Unit(this->pool.get_animations(HEAVY_TANK_EMPTY),
                            this->pool.get_animations(HEAVY_TANK_EMPTY),
                            this->pool.get_animations(HEAVY_TANK_EMPTY),
                            this->pool.get_animations(HEAVY_TANK_EMPTY),
                            this->pool.get_animations(HEAVY_TANK_EMPTY),
                            unit_code,posx,posy,MOVING1,HEAVY_TANK_EMPTY, unit_owner);

        case HEAVY_TANK_BLUE:
            return new Unit(this->pool.get_animations(HEAVY_TANK_BLUE),
                            this->pool.get_animations(HEAVY_TANK_BLUE),
                            this->pool.get_animations(HEAVY_TANK_BLUE),
                            this->pool.get_animations(HEAVY_TANK_BLUE_STAND),
                            this->pool.get_animations(HEAVY_TANK_BLUE),
                            unit_code,posx,posy,MOVING1,HEAVY_TANK_BLUE, unit_owner);

        case HEAVY_TANK_GREEN:
            return  new Unit(this->pool.get_animations(HEAVY_TANK_GREEN),
                             this->pool.get_animations(HEAVY_TANK_GREEN),
                             this->pool.get_animations(HEAVY_TANK_GREEN),
                             this->pool.get_animations(HEAVY_TANK_GREEN_STAND),
                             this->pool.get_animations(HEAVY_TANK_GREEN),
                             unit_code,posx,posy,MOVING1,HEAVY_TANK_GREEN, unit_owner);

        case HEAVY_TANK_RED:
            return new Unit(this->pool.get_animations(HEAVY_TANK_RED),
                            this->pool.get_animations(HEAVY_TANK_RED),
                            this->pool.get_animations(HEAVY_TANK_RED),
                            this->pool.get_animations(HEAVY_TANK_RED_STAND),
                            this->pool.get_animations(HEAVY_TANK_RED),
                            unit_code,posx,posy,MOVING1,HEAVY_TANK_RED , unit_owner);

        case HEAVY_TANK_YELLOW:
            return  new Unit(this->pool.get_animations(HEAVY_TANK_YELLOW),
                             this->pool.get_animations(HEAVY_TANK_YELLOW),
                             this->pool.get_animations(HEAVY_TANK_YELLOW),
                             this->pool.get_animations(HEAVY_TANK_YELLOW_STAND),
                             this->pool.get_animations(HEAVY_TANK_YELLOW),
                             unit_code,posx,posy,MOVING1, HEAVY_TANK_YELLOW, unit_owner);

        case MEDIUM_TANK_EMPTY:
            return new Unit(this->pool.get_animations(MEDIUM_TANK_EMPTY),
                            this->pool.get_animations(MEDIUM_TANK_EMPTY),
                            this->pool.get_animations(MEDIUM_TANK_EMPTY),
                            this->pool.get_animations(MEDIUM_TANK_EMPTY),
                            this->pool.get_animations(MEDIUM_TANK_EMPTY),
                            unit_code,posx,posy,MOVING1,MEDIUM_TANK_EMPTY, unit_owner);

        case MEDIUM_TANK_BLUE:
            return new Unit(this->pool.get_animations(MEDIUM_TANK_BLUE),
                            this->pool.get_animations(MEDIUM_TANK_BLUE),
                            this->pool.get_animations(MEDIUM_TANK_BLUE),
                            this->pool.get_animations(MEDIUM_TANK_BLUE_STAND),
                            this->pool.get_animations(MEDIUM_TANK_BLUE),
                            unit_code,posx,posy,MOVING1,MEDIUM_TANK_BLUE, unit_owner);

        case MEDIUM_TANK_GREEN:
            return  new Unit(this->pool.get_animations(MEDIUM_TANK_GREEN),
                             this->pool.get_animations(MEDIUM_TANK_GREEN),
                             this->pool.get_animations(MEDIUM_TANK_GREEN),
                             this->pool.get_animations(MEDIUM_TANK_GREEN_STAND),
                             this->pool.get_animations(MEDIUM_TANK_GREEN),
                             unit_code,posx,posy,MOVING1,MEDIUM_TANK_GREEN, unit_owner);

        case MEDIUM_TANK_RED:
            return new Unit(this->pool.get_animations(MEDIUM_TANK_RED),
                            this->pool.get_animations(MEDIUM_TANK_RED),
                            this->pool.get_animations(MEDIUM_TANK_RED),
                            this->pool.get_animations(MEDIUM_TANK_RED_STAND),
                            this->pool.get_animations(MEDIUM_TANK_RED),
                            unit_code,posx,posy,MOVING1,MEDIUM_TANK_RED , unit_owner);

        case MEDIUM_TANK_YELLOW:
            return  new Unit(this->pool.get_animations(MEDIUM_TANK_YELLOW),
                             this->pool.get_animations(MEDIUM_TANK_YELLOW),
                             this->pool.get_animations(MEDIUM_TANK_YELLOW),
                             this->pool.get_animations(MEDIUM_TANK_YELLOW_STAND),
                             this->pool.get_animations(MEDIUM_TANK_YELLOW),
                             unit_code,posx,posy,MOVING1, MEDIUM_TANK_YELLOW, unit_owner);

        case LIGHT_TANK_EMPTY:
            return new Unit(this->pool.get_animations(LIGHT_TANK_EMPTY),
                            this->pool.get_animations(LIGHT_TANK_EMPTY),
                            this->pool.get_animations(LIGHT_TANK_EMPTY),
                            this->pool.get_animations(LIGHT_TANK_EMPTY),
                            this->pool.get_animations(LIGHT_TANK_EMPTY),
                            unit_code,posx,posy,MOVING1,LIGHT_TANK_EMPTY, unit_owner);

        case LIGHT_TANK_BLUE:
            return new Unit(this->pool.get_animations(LIGHT_TANK_BLUE),
                            this->pool.get_animations(LIGHT_TANK_BLUE),
                            this->pool.get_animations(LIGHT_TANK_BLUE),
                            this->pool.get_animations(LIGHT_TANK_BLUE_STAND),
                            this->pool.get_animations(LIGHT_TANK_BLUE),
                            unit_code,posx,posy,MOVING1,LIGHT_TANK_BLUE, unit_owner);

        case LIGHT_TANK_GREEN:
            return  new Unit(this->pool.get_animations(LIGHT_TANK_GREEN),
                             this->pool.get_animations(LIGHT_TANK_GREEN),
                             this->pool.get_animations(LIGHT_TANK_GREEN),
                             this->pool.get_animations(LIGHT_TANK_GREEN_STAND),
                             this->pool.get_animations(LIGHT_TANK_GREEN),
                             unit_code,posx,posy,MOVING1,LIGHT_TANK_GREEN, unit_owner);

        case LIGHT_TANK_RED:
            return new Unit(this->pool.get_animations(LIGHT_TANK_RED),
                            this->pool.get_animations(LIGHT_TANK_RED),
                            this->pool.get_animations(LIGHT_TANK_RED),
                            this->pool.get_animations(LIGHT_TANK_RED_STAND),
                            this->pool.get_animations(LIGHT_TANK_RED),
                            unit_code,posx,posy,MOVING1,LIGHT_TANK_RED, unit_owner);

        case LIGHT_TANK_YELLOW:
            return  new Unit(this->pool.get_animations(LIGHT_TANK_YELLOW),
                             this->pool.get_animations(LIGHT_TANK_YELLOW),
                             this->pool.get_animations(LIGHT_TANK_YELLOW),
                             this->pool.get_animations(LIGHT_TANK_YELLOW_STAND),
                             this->pool.get_animations(LIGHT_TANK_YELLOW),
                             unit_code,posx,posy,MOVING1,LIGHT_TANK_YELLOW , unit_owner);

        case JEEP_EMPTY:
            return new Unit(this->pool.get_animations(JEEP_EMPTY),
                            this->pool.get_animations(JEEP_EMPTY),
                            this->pool.get_animations(JEEP_EMPTY),
                            this->pool.get_animations(JEEP_EMPTY),
                            this->pool.get_animations(JEEP_EMPTY),
                            unit_code,posx,posy,MOVING1,JEEP_EMPTY, unit_owner);

        case JEEP_BLUE:
            return new Unit(this->pool.get_animations(JEEP_BLUE),
                            this->pool.get_animations(JEEP_BLUE),
                            this->pool.get_animations(JEEP_BLUE),
                            this->pool.get_animations(JEEP_BLUE_STAND),
                            this->pool.get_animations(JEEP_BLUE),
                            unit_code,posx,posy,MOVING1,JEEP_BLUE, unit_owner);

        case JEEP_GREEN:
            return  new Unit(this->pool.get_animations(JEEP_GREEN),
                             this->pool.get_animations(JEEP_GREEN),
                             this->pool.get_animations(JEEP_GREEN),
                             this->pool.get_animations(JEEP_GREEN_STAND),
                             this->pool.get_animations(JEEP_GREEN),
                             unit_code,posx,posy,MOVING1,JEEP_GREEN, unit_owner);

        case JEEP_RED:
            return new Unit(this->pool.get_animations(JEEP_RED),
                            this->pool.get_animations(JEEP_RED),
                            this->pool.get_animations(JEEP_RED),
                            this->pool.get_animations(JEEP_RED_STAND),
                            this->pool.get_animations(JEEP_RED),
                            unit_code,posx,posy,MOVING1,JEEP_RED, unit_owner);

        case JEEP_YELLOW:
            return  new Unit(this->pool.get_animations(JEEP_YELLOW),
                             this->pool.get_animations(JEEP_YELLOW),
                             this->pool.get_animations(JEEP_YELLOW),
                             this->pool.get_animations(JEEP_YELLOW_STAND),
                             this->pool.get_animations(JEEP_YELLOW),
                             unit_code,posx,posy,MOVING1, JEEP_YELLOW, unit_owner);

        case MISILE_LAUNCHER_EMPTY:
            return new Unit(this->pool.get_animations(MISILE_LAUNCHER_EMPTY),
                            this->pool.get_animations(MISILE_LAUNCHER_EMPTY),
                            this->pool.get_animations(MISILE_LAUNCHER_EMPTY),
                            this->pool.get_animations(MISILE_LAUNCHER_EMPTY),
                            this->pool.get_animations(MISILE_LAUNCHER_EMPTY),
                            unit_code,posx,posy,MOVING1,MISILE_LAUNCHER_EMPTY, unit_owner);




        case MISILE_LAUNCHER_BLUE:
            return new Unit(this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE_STAND),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            unit_code,posx,posy,MOVING1,MISILE_LAUNCHER_BLUE, unit_owner);

        case MISILE_LAUNCHER_GREEN:
            return  new Unit(this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN_STAND),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             unit_code,posx,posy,MOVING1,MISILE_LAUNCHER_GREEN, unit_owner);

        case MISILE_LAUNCHER_RED:
            return new Unit(this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED_STAND),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            unit_code,posx,posy,MOVING1, MISILE_LAUNCHER_RED, unit_owner);

        case MISILE_LAUNCHER_YELLOW:
            return  new Unit(this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW_STAND),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             unit_code,posx,posy,MOVING1, MISILE_LAUNCHER_YELLOW, unit_owner);



        case COLORLESS_FLAG:
            return new Unit(this->pool.get_animations(COLORLESS_FLAG),
                            this->pool.get_animations(BLUE_FLAG),
                            this->pool.get_animations(GREEN_FLAG),
                            this->pool.get_animations(RED_FLAG),
                            this->pool.get_animations(YELLOW_FLAG),
                            unit_code,posx,posy,COLORLESS, COLORLESS_FLAG, unit_owner);
        case FORT_ALIVE:
            return new Unit(this->pool.get_animations(FORT_ALIVE),
                            this->pool.get_animations(FORT_ALIVE),
                            this->pool.get_animations(FORT_DEAD),
                            this->pool.get_animations(FORT_ALIVE),
                            this->pool.get_animations(FORT_ALIVE),
                            unit_code,posx,posy,DRINKING,FORT_ALIVE, unit_owner);

        case FACTORY_VEHICLES_ALIVE:
            return new Unit(this->pool.get_animations(FACTORY_VEHICLES_ALIVE),
                            this->pool.get_animations(FACTORY_VEHICLES_ALIVE),
                            this->pool.get_animations(FACTORY_VEHICLES_DEAD),
                            this->pool.get_animations(FACTORY_VEHICLES_ALIVE),
                            this->pool.get_animations(FACTORY_VEHICLES_ALIVE),
                            unit_code,posx,posy,DRINKING,FACTORY_VEHICLES_ALIVE, unit_owner);

        case FACTORY_ROBOTS_ALIVE:
            return new Unit(this->pool.get_animations(FACTORY_ROBOTS_ALIVE),
                            this->pool.get_animations(FACTORY_ROBOTS_ALIVE),
                            this->pool.get_animations(FACTORY_ROBOTS_DEAD),
                            this->pool.get_animations(FACTORY_ROBOTS_ALIVE),
                            this->pool.get_animations(FACTORY_ROBOTS_ALIVE),
                            unit_code,posx,posy,DRINKING,FACTORY_ROBOTS_ALIVE, unit_owner);

        case ROCK_BLOCK:
            return new Unit(this->pool.get_animations(ROCK_BLOCK),
                            this->pool.get_animations(ROCK_BLOCK),
                            this->pool.get_animations(ROCK_BLOCK),
                            this->pool.get_animations(ROCK_BLOCK),
                            this->pool.get_animations(ROCK_BLOCK),
                            unit_code,posx,posy,DRINKING,ROCK_BLOCK,unit_owner);

        case ICE_BLOCK:
            return new Unit(this->pool.get_animations(ICE_BLOCK),
                            this->pool.get_animations(ICE_BLOCK),
                            this->pool.get_animations(ICE_BLOCK),
                            this->pool.get_animations(ICE_BLOCK),
                            this->pool.get_animations(ICE_BLOCK),
                            unit_code,posx,posy,DRINKING,ICE_BLOCK,unit_owner);

        case BRIDGE_CONCRETE_VERTICAL:
            return new Unit(this->pool.get_animations(BRIDGE_CONCRETE_VERTICAL),
                            this->pool.get_animations(BRIDGE_CONCRETE_VERTICAL),
                            this->pool.get_animations(BRIDGE_CONTRETE_VERTICAL_DESTROYED),
                            this->pool.get_animations(BRIDGE_CONCRETE_VERTICAL),
                            this->pool.get_animations(BRIDGE_CONCRETE_VERTICAL),
                            unit_code,posx,posy,DRINKING,BRIDGE_CONCRETE_VERTICAL,unit_owner);

        case BRIDGE_WOOD_VERTICAL:
            return new Unit(this->pool.get_animations(BRIDGE_WOOD_VERTICAL),
                            this->pool.get_animations(BRIDGE_WOOD_VERTICAL),
                            this->pool.get_animations(BRIDGE_WOOD_VERTICAL_DESTROYED),
                            this->pool.get_animations(BRIDGE_WOOD_VERTICAL),
                            this->pool.get_animations(BRIDGE_WOOD_VERTICAL),
                            unit_code,posx,posy,DRINKING,BRIDGE_WOOD_VERTICAL,unit_owner);


        case BRIDGE_CONCRETE_HORIZONTAL:
            return new Unit(this->pool.get_animations(BRIDGE_CONCRETE_HORIZONTAL),
                            this->pool.get_animations(BRIDGE_CONCRETE_HORIZONTAL),
                            this->pool.get_animations(BRIDGE_CONTRETE_HORIZONTAL_DESTROYED),
                            this->pool.get_animations(BRIDGE_CONCRETE_HORIZONTAL),
                            this->pool.get_animations(BRIDGE_CONCRETE_HORIZONTAL),
                            unit_code,posx,posy,DRINKING,BRIDGE_CONCRETE_VERTICAL,unit_owner);


        case BRIDGE_WOOD_HORIZONTAL:
            return new Unit(this->pool.get_animations(BRIDGE_WOOD_HORIZONTAL),
                            this->pool.get_animations(BRIDGE_WOOD_HORIZONTAL),
                            this->pool.get_animations(BRIDGE_WOOD_HORIZONTAL_DESTROYED),
                            this->pool.get_animations(BRIDGE_WOOD_HORIZONTAL),
                            this->pool.get_animations(BRIDGE_WOOD_HORIZONTAL),
                            unit_code,posx,posy,DRINKING,BRIDGE_WOOD_HORIZONTAL,unit_owner);

        case LASER_BULLET:
            return new Unit(this->pool.get_animations(LASER_BULLET),
                            this->pool.get_animations(LASER_BULLET),
                            this->pool.get_animations(BULLET_DEAD),
                            this->pool.get_animations(LASER_BULLET),
                            this->pool.get_animations(LASER_BULLET),
                            unit_code,posx,posy,MOVING1,LASER_BULLET, unit_owner);
        case PYRO_BULLET:
            return new Unit(this->pool.get_animations(PYRO_BULLET),
                            this->pool.get_animations(PYRO_BULLET),
                            this->pool.get_animations(BULLET_DEAD),
                            this->pool.get_animations(PYRO_BULLET),
                            this->pool.get_animations(PYRO_BULLET),
                            unit_code,posx,posy,MOVING1,PYRO_BULLET,unit_owner);
        case TOUGHT_BULLET:
            return new Unit(this->pool.get_animations(TOUGHT_BULLET),
                            this->pool.get_animations(TOUGHT_BULLET),
                            this->pool.get_animations(BULLET_DEAD),
                            this->pool.get_animations(TOUGHT_BULLET),
                            this->pool.get_animations(TOUGHT_BULLET),
                            unit_code,posx,posy,MOVING1,TOUGHT_BULLET, unit_owner);

        case HCP_BULLET:
            return new Unit(this->pool.get_animations(TOUGHT_BULLET),
                            this->pool.get_animations(TOUGHT_BULLET),
                            this->pool.get_animations(BULLET_DEAD),
                            this->pool.get_animations(TOUGHT_BULLET),
                            this->pool.get_animations(TOUGHT_BULLET),
                            unit_code,posx,posy,MOVING1,HCP_BULLET, unit_owner);
        default:
            return new Unit(this->pool.get_animations(TOUGHT_BULLET),
                            this->pool.get_animations(TOUGHT_BULLET),
                            this->pool.get_animations(BULLET_DEAD),
                            this->pool.get_animations(TOUGHT_BULLET),
                            this->pool.get_animations(TOUGHT_BULLET),
                            unit_code,posx,posy,MOVING1,HCP_BULLET, unit_owner);
    }

    return new Unit(this->pool.get_animations(TOUGHT_BULLET),
                    this->pool.get_animations(TOUGHT_BULLET),
                    this->pool.get_animations(BULLET_DEAD),
                    this->pool.get_animations(TOUGHT_BULLET),
                    this->pool.get_animations(TOUGHT_BULLET),
                    unit_code,posx,posy,MOVING1,HCP_BULLET, unit_owner);

}
