#pragma once
#include <iostream>
#include <vector>
#include "Ship.h"

int PrintShopInventory(vector<Weapon> inventory, int HealthCap, int CurrHealth);

int PrintSellOptions(vector<Weapon> inventory);

bool getNextEvent(Ship* PlayerShip, int EventCode, int galaxy, int* galacticCredits);

int getEventCode(int EventCode);

int getNewEventCode();

