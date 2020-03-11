#pragma once
#include <iostream>
#include <memory>
#include "Weapon.h"
using namespace std;

class Ship {

private:
    string ShipName;
    int HealthCap = 0;
    int ShipHealth = HealthCap;
    int ShieldCap = 0;
    int ShieldHealth = ShieldCap;
    char ShipType;
    string color;
    double evasion;
    int weaponCapacity;
    int numWeps;
    int power;
    vector<Weapon> Weapons;


public:
    Ship();

    Ship(char ShipType, string ShipName);

    string getShipName();

    char getShipType();

    void setShipHealth(int ShipHealth);

    int getShipHealth();

    int getShipHealthCap();

    void setSheildHealth(int ShieldHealth);

    int getShieldCap();

    int getSheildHealth();

    void setEvasion(double evasion);

    double getEvasion();

    vector<Weapon> getWeapons();

    void setWepCapacity(int weaponCapacity);

    int getWepCapacity();

    int getNumWeps();

    void addWeapon(Weapon newWep);

    void deleteWeapon(int index);

    void getWepSet();

    void setPower(int power);

    int getPower();

    string getShipColor();

    bool wepMatch(Ship* ship, Weapon weapon);


};

