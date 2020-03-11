#pragma once
#include <iostream>
#include <memory>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

class Weapon {
private:
    string type;
    string name;
    string status;
    int damage;
    int power;
    int chargeTime;
    int chargeTurns;
    int disabledTurns;
    int disableTurns;
    int mult;
    int seed;
    int priceTier;

public:
    Weapon();

    Weapon(int seed);

    string getWepName();

    string getWepType();

    int getDamage();

    int getWepPower();

    int getChrTime();

    int getDisTurns();

    int getChrTurns();

    void setChrTurns(int in);

    int getMulti();

    void setMulti(int x);

    int getSeed();

    int getPriceTier();

    void setStatus(string in);

    string getStatus();

    int getDisabledTurns();

    void setDisabledTurns(int in);

    int getDISABLETurns();

};