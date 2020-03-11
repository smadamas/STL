#include <iostream>
#include <memory>
#include "Ship.h"
using namespace std;


//Constructors

Ship::Ship() {
    HealthCap = 0;
    ShipHealth = HealthCap;
    ShieldCap = 0;
    ShieldHealth = ShieldCap;
    ShipType = 'D';
    ShipName = "\n\nThere was an error, check main and Ship.cpp\n";
    color = "The wrong color";
    evasion = 0.0;
    weaponCapacity = 0;
    numWeps = 0;
    Weapons = {};
    power = 0;
}

Ship::Ship(char ShipType, string ShipName) {
    this->ShipName = ShipName;
    this->ShipType = ShipType;
    //Playerships
    if (ShipType == 'A') {
        HealthCap = 21;
        ShieldCap = 8;
        ShieldHealth = ShieldCap;
        color = "beige";
        evasion = 10;
        weaponCapacity = 4;
        Weapons = { Weapon(0), Weapon(11) };
        numWeps = 2;
        power = 10;
    }
    else if (ShipType == 'B') {
        HealthCap = 10;
        ShieldCap = 8;
        ShieldHealth = ShieldCap;
        color = "cherry red";
        evasion = 13;
        weaponCapacity = 3;
        Weapons = { Weapon(0), Weapon(19) };
        numWeps = 2;
        power = 8;
    }
    else if (ShipType == 'C') {
        HealthCap = 15;
        ShieldCap = 8;
        ShieldHealth = ShieldCap;
        color = "lime green";
        evasion = 11;
        weaponCapacity = 3;
        Weapons = { Weapon(10), Weapon(19) };
        numWeps = 2;
        power = 14;
    }
    //Easy Enemy Ships
    else if (ShipType == 'D') {
        HealthCap = 7;
        ShieldCap = 5;
        ShieldHealth = ShieldCap;
        color = "black";
        evasion = 5;
        weaponCapacity = 2;
        Weapons = { Weapon(10), Weapon(0) };
        numWeps = 2;
        power = 8;
    }
    else if (ShipType == 'E') {
        HealthCap = 15;
        ShieldCap = 5;
        ShieldHealth = ShieldCap;
        color = "black";
        evasion = 7;
        weaponCapacity = 3;
        Weapons = { Weapon(11), Weapon(0), Weapon(19) };
        numWeps = 3;
        power = 14;
    }
    else if (ShipType == 'F') {
        HealthCap = 12;
        ShieldCap = 5;
        ShieldHealth = ShieldCap;
        color = "black";
        evasion = 6;
        weaponCapacity = 3;
        Weapons = { Weapon(0), Weapon(0), Weapon(0) };
        numWeps = 3;
        power = 11;
    }
    //Hard Enemy Ships
    else if (ShipType == 'G') {
        HealthCap = 14;
        ShieldCap = 5;
        ShieldHealth = ShieldCap;
        color = "black";
        evasion = 7;
        weaponCapacity = 3;
        Weapons = { Weapon(4), Weapon(19) };
        numWeps = 2;
        power = 12;
    }
    else if (ShipType == 'H') {
        HealthCap = 14;
        ShieldCap = 5;
        ShieldHealth = ShieldCap;
        color = "black";
        evasion = 6;
        weaponCapacity = 3;
        Weapons = { Weapon(1), Weapon(12), Weapon(20) };
        numWeps = 3;
        power = 12;
    }
    else if (ShipType == 'I') {
        HealthCap = 20;
        ShieldCap = 10;
        ShieldHealth = ShieldCap;
        color = "black";
        evasion = 7;
        weaponCapacity = 3;
        Weapons = { Weapon(1), Weapon(11), Weapon(22) };
        numWeps = 3;
        power = 16;
    }
    //Monsters
    else if (ShipType == 'J') {
        HealthCap = 30;
        color = "green";
        evasion = 7;
        weaponCapacity = 2;
        Weapons = { Weapon(27), Weapon(29) };
        numWeps = 2;
        power = 16;
    }
    else if (ShipType == 'K') {
        HealthCap = 40;
        color = "purple";
        evasion = 9;
        weaponCapacity = 2;
        Weapons = { Weapon(28), Weapon(30) };
        numWeps = 2;
        power = 16;
    }
    ShipHealth = HealthCap;
}

//Getters and Setters

string Ship::getShipName() {
    return ShipName;
}
char Ship::getShipType() {
    return ShipType;
}
void Ship::setShipHealth(int ShipHealth) {
    this->ShipHealth = ShipHealth;
}
int Ship::getShipHealthCap() {
    return HealthCap;
}
int Ship::getShipHealth() {
    return ShipHealth;
}
void Ship::setSheildHealth(int ShieldHealth) {
    this->ShieldHealth = ShieldHealth;
}
int Ship::getShieldCap() {
    return ShieldCap;
}
int Ship::getSheildHealth() {
    return ShieldHealth;
}
void Ship::setEvasion(double evasion) {
    this->evasion = evasion;
}
double Ship::getEvasion() {
    return evasion;
}
vector<Weapon> Ship::getWeapons() {
    return Weapons;
}
void Ship::setWepCapacity(int weaponCapacity) {
    this->weaponCapacity = weaponCapacity;
}
int Ship::getWepCapacity() {
    return weaponCapacity;
}
int Ship::getNumWeps() {
    return numWeps;
}
void Ship::addWeapon(Weapon newWep) {
    Weapons.push_back(newWep);
    numWeps++;
}
void Ship::deleteWeapon(int index) {
    Weapons.erase(Weapons.begin() + index);
    numWeps--;
}


void Ship::getWepSet() {
    int calc = 0;
    cout << "Names:         ";
    for (int i = 0; i < this->Weapons.size(); i++) {
        cout << setw(40) << Weapons[i].getWepName();
    }
    cout << endl;
    cout << "Type:          ";
    for (int i = 0; i < this->Weapons.size(); i++) {
        cout << setw(40) << Weapons[i].getWepType();
    }
    cout << endl;
    cout << "Damage:        ";
    for (int i = 0; i < this->Weapons.size(); i++) {
        cout << setw(40) << Weapons[i].getDamage();
    }
    cout << endl;
    cout << "Power Req:     ";
    for (int i = 0; i < this->Weapons.size(); i++) {
        cout << setw(40) << Weapons[i].getWepPower();
    }
    cout << endl;
    cout << "Charge Turns:  ";
    for (int i = 0; i < this->Weapons.size(); i++) {
        cout << setw(40) << Weapons[i].getChrTime();
    }
    cout << endl;
    cout << "Disable Turns: ";
    for (int i = 0; i < this->Weapons.size(); i++) {
        cout << setw(40) << Weapons[i].getDisTurns();
    }
    cout << endl;
    cout << "Multiplicity:  ";
    for (int i = 0; i < this->Weapons.size(); i++) {
        cout << setw(40) << Weapons[i].getMulti();
    }
    cout << endl;
}

void Ship::setPower(int power) {
    this->power = power;
}
int Ship::getPower() {
    return power;
}
string Ship::getShipColor() {
    return color;
}

bool Ship::wepMatch(Ship* ship, Weapon weapon) {
    for (int i = 0; i < ship->getWeapons().size(); i++) {
        if (ship->getWeapons().at(i).getSeed() == weapon.getSeed()) {
            ship->getWeapons().at(i).setMulti(ship->getWeapons().at(i).getMulti() + 1);
            return true;
        }
    }
    return false;
}




