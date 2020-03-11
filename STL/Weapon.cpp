#include <iostream>
#include <memory>
#include <iomanip>
#include <vector>
#include <string>
#include "Weapon.h"
using namespace std;



    Weapon::Weapon() {
        type = "None";
        name = "None";
        status = "(dormant)";
        damage = 0;
        power = 0;
        chargeTime = 0;
        chargeTurns = 0;
        disabledTurns = 0;
        disableTurns = 0;
        mult = 0;
        seed = 0;
        priceTier = 0;
    }

    Weapon::Weapon(int seed) {
        this->seed = seed;

        //Lasers
        if (seed == 0) {
            name = "Basic Laser";
            damage = 1;
            power = 1;
            chargeTime = 0;
            disableTurns = 0;
            mult = 1;
            type = "Laser";
            priceTier = 0;
        }
        else if (seed == 1) {
            name = "Double Laser";
            damage = 1;
            power = 1;
            chargeTime = 0;
            disableTurns = 0;
            mult = 2;
            type = "Laser";
            priceTier = 1;
        }
        else if (name == "Big Zapper") {
            damage = 3;
            power = 2;
            chargeTime = 2;
            disableTurns = 0;
            mult = 1;
            seed = 2;
            type = "Laser";
            priceTier = 1;
        }
        else if (seed == 3) {
            name = "Big Zapper MKII";
            damage = 5;
            power = 3;
            chargeTime = 2;
            disableTurns = 0;
            mult = 1;
            type = "Laser";
            priceTier = 2;
        }
        else if (seed == 4) {
            name = "Piercing Laser";
            damage = 3;
            power = 1;
            chargeTime = 2;
            disableTurns = 0;
            mult = 1;
            type = "Laser";
            priceTier = 2;
        }
        else if (seed == 5) {
            name = "Piercing Laser MKII";
            damage = 5;
            power = 2;
            chargeTime = 3;
            disableTurns = 0;
            mult = 1;
            type = "Laser";
            priceTier = 3;
        }
        else if (seed == 6) {
            name = "Beefy Laser";
            damage = 5;
            power = 3;
            chargeTime = 1;
            disableTurns = 0;
            mult = 1;
            type = "Laser";
            priceTier = 3;
        }
        else if (seed == 7) {
            name = "Molecular Separator";
            damage = 6;
            power = 2;
            chargeTime = 2;
            disableTurns = 0;
            mult = 1;
            type = "Laser";
            priceTier = 3;
        }
        else if (seed == 8) {
            name = "Jodie";
            damage = 4;
            power = 1;
            chargeTime = 1;
            disableTurns = 0;
            mult = 1;
            type = "Laser";
            priceTier = 4;
        }
        else if (seed == 9) {
            name = "Xerxes";
            damage = 10;
            power = 4;
            chargeTime = 3;
            disableTurns = 1;
            mult = 1;
            type = "Laser";
            priceTier = 4;
        }

        //Missiles
        if (seed == 10) {
            name = "Basic Missile";
            damage = 2;
            power = 1;
            chargeTime = 1;
            disableTurns = 0;
            mult = 1;
            type = "Missile";
            priceTier = 0;
        }
        else if (seed == 11) {
            name = "Apollo Missile";
            damage = 2;
            power = 2;
            chargeTime = 0;
            disableTurns = 0;
            mult = 1;
            type = "Missile";
            priceTier = 1;
        }
        else if (seed == 12) {
            name = "Hole Puncher";
            damage = 4;
            power = 2;
            chargeTime = 1;
            disableTurns = 0;
            mult = 1;
            type = "Missile";
            priceTier = 1;
        }
        else if (seed == 13) {
            name = "Hole Puncher MKII";
            damage = 6;
            power = 3;
            chargeTime = 1;
            disableTurns = 0;
            mult = 1;
            type = "Missile";
            priceTier = 2;
        }
        else if (seed == 14) {
            name = "Double Apollo Missile";
            damage = 2;
            power = 1;
            chargeTime = 0;
            disableTurns = 0;
            mult = 2;
            type = "Missile";
            priceTier = 2;
        }
        else if (seed == 15) {
            name = "Big Iron";
            damage = 2;
            power = 3;
            chargeTime = 3;
            disableTurns = 0;
            mult = 3;
            type = "Missile";
            priceTier = 3;
        }
        else if (seed == 16) {
            name = "Blunderbuss";
            damage = 8;
            power = 3;
            chargeTime = 2;
            disableTurns = 0;
            mult = 1;
            type = "Missile";
            priceTier = 3;
        }
        else if (seed == 17) {
            name = "Annette";
            damage = 5;
            power = 1;
            chargeTime = 0;
            disableTurns = 0;
            mult = 1;
            type = "Missile";
            priceTier = 4;
        }
        else if (seed == 18) {
            name = "The Whopper";
            damage = 12;
            power = 4;
            chargeTime = 5;
            disableTurns = 0;
            mult = 1;
            type = "Missile";
            priceTier = 4;
        }

        //Pulse
        else if (seed == 19) {
            name = "Sparky Pulse Gun";
            damage = 0;
            power = 2;
            chargeTime = 1;
            disableTurns = 1;
            mult = 1;
            type = "Pulse";
            priceTier = 0;
        }
        else if (seed == 20) {
            name = "Pulse Absorber";
            damage = 0;
            power = 3;
            chargeTime = 0;
            disableTurns = 0;
            mult = 1;
            type = "Pulse";
            priceTier = 1;
        }
        else if (seed == 21) {
            name = "Formidable Electronic Disabler Ray";
            damage = 0;
            power = 3;
            chargeTime = 1;
            disableTurns = 2;
            mult = 1;
            type = "Pulse";
            priceTier = 1;
        }
        else if (seed == 22) {
            name = "Pulse Blaster";
            damage = 0;
            power = 3;
            chargeTime = 1;
            disableTurns = 3;
            mult = 1;
            type = "Pulse";
            priceTier = 2;
        }
        else if (seed == 23) {
            name = "Zapdos";
            damage = 0;
            power = 4;
            chargeTime = 3;
            disableTurns = 3;
            mult = 2;
            type = "Pulse";
            priceTier = 2;
        }
        else if (seed == 24) {
            name = "The Defibrilator";
            damage = 0;
            power = 2;
            chargeTime = 1;
            disableTurns = 2;
            mult = 1;
            type = "Pulse";
            priceTier = 3;
        }
        else if (seed == 25) {
            name = "Gloria";
            damage = 0;
            power = 2;
            chargeTime = 4;
            disableTurns = 6;
            mult = 1;
            type = "Pulse";
            priceTier = 4;
        }
        else if (seed == 26) {
            name = "Zeus' Thunderbolt";
            damage = 4;
            power = 3;
            chargeTime = 5;
            disableTurns = 2;
            mult = 4;
            type = "Pulse";
            priceTier = 4;
        }


        //Monsters
        else if (seed == 27) {
            name = "Bite";
            damage = 4;
            power = 0;
            chargeTime = 0;
            disableTurns = 0;
            mult = 1;
            type = "Monster";
            priceTier = 0;
        }
        else if (seed == 28) {
            name = "Corrosive Breath";
            damage = 4;
            power = 0;
            chargeTime = 1;
            disableTurns = 0;
            mult = 1;
            type = "Monster";
            priceTier = 0;
        }
        else if (seed == 29) {
            name = "Tail Whip";
            damage = 7;
            power = 0;
            chargeTime = 0;
            disableTurns = 0;
            mult = 1;
            type = "Monster";
            priceTier = 0;
        }
        else if (seed == 30) {
            name = "Headbutt";
            damage = 8;
            power = 0;
            chargeTime = 1;
            disableTurns = 0;
            mult = 1;
            type = "Monster";
            priceTier = 0;
        }
        chargeTurns = chargeTime;
        disableTurns = 0;
        status = "(dormant)";

    }

    string Weapon::getWepName() {
        return name;
    }
    string Weapon::getWepType() {
        return type;
    }
    int Weapon::getDamage() {
        return damage;
    }
    int Weapon::getWepPower() {
        return power;
    }
    int Weapon::getChrTime() {
        return chargeTime;
    }
    int Weapon::getChrTurns() {
        return chargeTurns;
    }
    void Weapon::setChrTurns(int in) {
        chargeTurns = in;
    }
    int Weapon::getDisTurns() {
        return disableTurns;
    }
    int Weapon::getMulti() {
        return mult;
    }
    void Weapon::setMulti(int x) {
        mult = x;
    }
    int Weapon::getSeed() {
        return seed;
    }
    int Weapon::getPriceTier() {
        return priceTier;
    }
    void Weapon::setStatus(string in) {
        status = in;
    }
    string Weapon::getStatus() {
        return status;
    }
    int Weapon::getDisabledTurns() {
        return disabledTurns;
    }
    void Weapon::setDisabledTurns(int in) {
        disabledTurns = in;
    }
    int Weapon::getDISABLETurns() {
        return disableTurns;
    }


