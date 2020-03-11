#pragma once
#include <iostream>
#include "RandomEvents.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <iomanip>
#include "RandomEvents.h"
#include "Combat.h"
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <map>
using namespace std;


//Stuff For timeout inputs (see asteroids)
condition_variable cv;
int value;

void read_value() {
    cin >> value;
    cv.notify_one();
}

//Event Code management
bool getNextEvent(Ship* PlayerShip, int EventCode, int galaxy, int* galacticCredits) {
    string answer;
    if (galaxy == 1) {
        if (0 < EventCode && EventCode <= 5) {
            //Shop
            int randWep;
            int input;
            vector<Weapon> inventory;
            bool Buy = true;
            for (int i = 0; i < 8; i++) {
                randWep = rand() % 26 + 1;
                inventory.push_back(Weapon(randWep));
            }

            if (EventCode >= 2) {
                cout << "\nAs you dock at an unremarkable planet for a pit stop, you realize that there is a small merchants' district" << endl;
                cout << "surrounding you. People of various alien races bustle about the trashy-looking shops as a veil of sand washes" << endl;
                cout << " over the forgotten town. You consult the merchants for their wares." << endl;
            }
            else if (EventCode == 3 || EventCode == 4) {
                cout << "\nYou see ahead of you a mighty rebel warship. Relieved, you land and they repair your ship completely, give you" << endl;
                cout << "some extra Galactic Credits for the road, and offer some weapons for sale." << endl;
                galacticCredits += 24;
                PlayerShip->setShipHealth(PlayerShip->getShipHealthCap());
            }
            else {
                cout << "\nA medium sized, war-torn ship idles peacefully along a planet's outer rings. It is colorfully labeled with" << endl;
                cout << "a bolded \"WEAPONS AND SUPPLIES\" on its broadside. You pull up along side at what appears to be a service" << endl;
                cout << "Window and a hooded figure appears with a menu of wares." << endl;
            }


            while (true) {
                if (Buy) {
                    cout << "\nCurrent Inventory:" << endl;
                    PlayerShip->getWepSet();
                    int counter = PrintShopInventory(inventory, int(PlayerShip->getShipHealthCap()), int(PlayerShip->getShipHealth()));
                    cout << "Would you like to buy anything? Enter the corresponding number or quit the menu." << endl;
                    cout << "Galactic Credits: " << *galacticCredits << endl;
                    cout << endl;
                    cout << "Current Hull Health: " << PlayerShip->getShipHealth() << " / " << PlayerShip->getShipHealthCap() << endl << endl;
                    cout << "Your choice: " << endl;

                    cin >> input;

                    if (input == counter) {
                        cin.ignore();
                        cout << "\nAre you sure you want to quit and head to the next location? Enter Y or N" << endl;
                        cin >> answer;
                        if (answer == "Y" || answer == "y") {
                            break;
                        }
                    }
                    else if (input == counter - 1) {
                        PlayerShip->setShipHealth(PlayerShip->getShipHealthCap());
                    }
                    else if (input == counter - 2) {
                        Buy = !Buy;
                    }
                    else if (input > counter || !isdigit(input)) {
                        continue;
                    }
                    else {
                        
                        if (PlayerShip->wepMatch(PlayerShip, inventory.at(input - 1)) == true) {
                            cout << "\nYou already have this weapon." << endl;
                        }
                        else if (PlayerShip->getWepCapacity() == PlayerShip->getNumWeps()) {
                            cout << "\nYou do not have enough space on your ship!" << endl;
                        }
                        else if (*galacticCredits <= ((inventory.at(input - 1).getPriceTier()) * 10)) {
                            cout << "\nYou dont have enough money!" << endl;
                        }
                        else {
                            PlayerShip->addWeapon(inventory.at(input - 1));
                            *galacticCredits -= (inventory.at(input - 1).getPriceTier()) * 10;
                            inventory.erase(inventory.begin() + input - 1);
                        }
                        
                    }
                }
                else {
                    int counter = PrintSellOptions(PlayerShip->getWeapons());
                    
                    cout << "Would you like to sell? Enter the corresponding number or quit the menu." << endl;
                    cout << "Galactic Credits: " << *galacticCredits << endl;
                    cout << endl;
                    cout << "Current Hull Health: " << PlayerShip->getShipHealth() << " / " << PlayerShip->getShipHealthCap() << endl << endl;
                    cout << "Your choice: " << endl;

                    cin >> input;

                    if (input == counter) {
                        cin.ignore();
                        cout << "\nAre you sure you want to quit and head to the next location? Enter Y or N" << endl;
                        cin >> answer;
                        if (answer == "Y" || answer == "y") {
                            break;
                        }
                    }
                    else if (input == counter - 1) {
                        Buy = !Buy;
                    }
                    else if (input > counter) {
                        continue;
                    }
                    else {
                        if (PlayerShip->getWeapons().size() >= 2) {
                            int sellPrice;
                            sellPrice = PlayerShip->getWeapons().at(input - 1).getPriceTier();
                            sellPrice += 5;
                            sellPrice *= 10;
                            sellPrice = floor(sellPrice * .6);
                            *galacticCredits += sellPrice;
                        }
                        else {
                            cout << "You can't sell your last weapon!!" << endl;
                        }
                        PlayerShip->getWeapons().erase(PlayerShip->getWeapons().begin() + input - 1);
                    }
                }
                
            }

            inventory.clear();
        }
        else if (EventCode == 6 || EventCode == 7) {
            //Dodge asteroids
            cout << "Oh no! You've come upon a very inconvenient field of asteroids, and you're gonna have to navigate your way out!" << endl;
            cout << "Huge space rocks are hurdling at your ship from all sides, so you're gonna have to do some quick thinking to get" << endl;
            cout << "get yourself out of this pinch. Check out the patterns and find the odd ones out, and BE QUICK! Remember where you've" << endl;
            cout << "been, because you'll need to recall them all to assemble space navigation coordinates to get out of this mess." << endl;

            string coordinates = "nothing";
            int correctAnswer;

            for (unsigned int i = 1; i <= 5; i++) {

                //Timed print and select with int answer
                cout << "Enter your answer quick: ";
                thread th(read_value);

                mutex mtx;
                unique_lock<mutex> lck(mtx);
                while (cv.wait_for(lck, chrono::seconds(2)) == cv_status::timeout)
                {
                    cout << "\nTime-Out: 2 second:";
                    cout << "\nPlease enter the input:";
                }
                cout << "You entered: " << value << '\n';
                th.join();

                //Check if right, if not ->hull damage, restart
                if (value == correctAnswer) {
                    //Append correct answer to coordinates string
                    coordinates += "ing";


                    //Call Helper with map and add a new item
                    map<int, string> AsteroidAnswers;
                    getAsteroidsSet(&AsteroidAnswers);
                    //Create new option set and correctAnswer
                }
                else {
                    PlayerShip->setShipHealth(PlayerShip->getShipHealth() - 1);
                    if (PlayerShip->getShipHealth() <= 0) {
                        return false;
                    }
                }

            }



                return true;
        }
        else if (EventCode == 8 || EventCode == 9) {
            //Fight with tough bandit
            int ShipSeed;
            Ship EnemyShip;
            ShipSeed = rand() % 3 + 1;
            if (ShipSeed == 1) {
                EnemyShip = Ship('G', "Pirate");
            }
            else if (ShipSeed == 2) {
                EnemyShip = Ship('H', "Bounty Hunter");
            }
            else {
                EnemyShip = Ship('I', "Bounty Hunter");
            }

            bool Win = startCombat(PlayerShip, &EnemyShip);
            cout << endl << "Here's the fight's result: " << Win << endl;
            if (!Win) {
                return false;
            }
            else { return true; }
        }
        else if (9 < EventCode && EventCode <= 15) {
            //Fight with a pirate/bandit
            int ShipSeed;
            Ship EnemyShip;
            ShipSeed = rand() % 3 + 1;
            if (ShipSeed == 1) {
                EnemyShip = Ship('D', "Pirate");
            }
            else if (ShipSeed == 2) {
                EnemyShip = Ship('E', "Bandit");
            }
            else {
                EnemyShip = Ship('F', "Bandit");
            }

            bool Win = startCombat(PlayerShip, &EnemyShip);
            if (!Win) {
                cout << "Your ship exploded! Now you're dead." << endl;
                return false;
            }
            else { 
                cout << "The enemy ship explodes and you know you've won the fight. Hurrah!" << endl;
                return true; 
            }
            //Collect money or parts from the win? Small random chance of getting new weapon
            
        }
        else if (EventCode == 16) {
            //Optional warp to galaxy 3
            cout << "You've stumbled across a wormhole! Don't fear though, for it has been well mapped and documented," << endl;
            cout << "and you see many ships coming in and out of it even now. Take the wormhole to warp to the third and" << endl;
            cout << "final galaxy? It won't be easy but you'll make record time! Type Y or N for yes or no." << endl;
            cout << "\nTake the wormhole to galaxy 3? (Y/N): " << endl;

            cin >> answer;
            if (answer == "y" || answer == "Y") {
                galaxy = 3;
            }
        }
        else if (16 < EventCode && EventCode <= 19) {
            //Fight with a space monster
        }
        else if (EventCode == 20) {
            //Something special reward Xtra EZ cheat code ahahahaha
        }
    }
    else if (galaxy == 2) {

    }
    else if (galaxy == 3) {

    }
    else { cout << "Something broke!" << endl; }

    return true;
}

int getEventCode(int EventCode) {
    return EventCode;
}

int getNewEventCode() {
    //Only for Developer Mode
    cout << "Please enter desired code: ";
    int EventCode;
    cin >> EventCode;
    cout << endl;

    //Enable for playthroughs
    //EventCode = rand() % 20 + 1;
    return EventCode;
}

void getAsteroidsSet(map<int, string> *AsteroidAnswers) {
    //Only for Developer Mode
    //cout << "Please enter desired code: ";
    int random;
    //cin >> EventCode;
    //cout << endl;

    //Enable for playthroughs
    random = rand() % 15 + 1;
    switch (random) {
    case 1:
        cout << "1. 15   2. 60" << endl;
        cout << "3. 20   4. 45" << endl;
        AsteroidAnswers->emplace(3, "20");
        break;
    case 2:
        cout << "1. dove   2. crane" << endl;
        cout << "3. gull   4. penguin" << endl;
        AsteroidAnswers->emplace(4, "penguin");
        break;
    case 3:
        cout << "1. oak   2. bent" << endl;
        cout << "3. pine  4. wind" << endl;
        AsteroidAnswers->emplace(1, "oak");
        break;
    case 4:
        cout << "1. !   2. $" << endl;
        cout << "3. #   4. %" << endl;
        AsteroidAnswers->emplace(1, "!");
        break;
    case 5:
        cout << "1. 49   2. 18" << endl;
        cout << "3. 14   4. 7" << endl;
        AsteroidAnswers->emplace(2, "18");
        break;
    case 6:
        cout << "1. 103  2. 129" << endl;
        cout << "3. 42   4. 978" << endl;
        AsteroidAnswers->emplace(3, "42");
        break;
    case 7:
        cout << "1. and  2. of" << endl;
        cout << "3. or   4. when" << endl;
        AsteroidAnswers->emplace(4, "when");
        break;
    case 8:
        cout << "1. alpha   2. foxtrot" << endl;
        cout << "3. igloo   4. delta" << endl;
        AsteroidAnswers->emplace(3, "igloo");
        break;
    case 9:
        cout << "1. 15   2. 16" << endl;
        cout << "3. 18   4. 14" << endl;
        AsteroidAnswers->emplace(1, "15");
        break;
    case 10:
        cout << "1. 54   2. 60" << endl;
        cout << "3. 12   4. 26" << endl;
        AsteroidAnswers->emplace(4, "26");
        break;
    case 11:
        cout << "1. sun   2. wed" << endl;
        cout << "3. phe   4. sat" << endl;
        AsteroidAnswers->emplace(3, "20");
        break;
    case 12:
        cout << "1. sedimentary    2. volatile" << endl;
        cout << "3. metamorphic    4. igneous" << endl;
        AsteroidAnswers->emplace(2, "volatile");
        break;
    case 13:
        cout << "1. 18    2. 1800" << endl;
        cout << "3. 180   4. 90" << endl;
        AsteroidAnswers->emplace(4, "90");
        break;
    case 14:
        cout << "1. begin   2. resolve" << endl;
        cout << "3. induce  4. commence" << endl;
        AsteroidAnswers->emplace(2, "resolve");
        break;
    case 15:
        cout << "1. 80   2. 175" << endl;
        cout << "3. 25   4. 100" << endl;
        AsteroidAnswers->emplace(1, "80");
        break;
    }
        
}

int PrintShopInventory(vector<Weapon> inventory, int HealthCap, int CurrHealth) {
    int counter = 1;
    cout << setw(40);
    cout << left << "\n\nItem";
    cout << right << "Price" << endl;
    for (int i = 0; i < inventory.size()-1; i++) {
        cout << left << counter << left << ". ";
        cout << setw(40) << left << inventory.at(i).getWepName();
        cout << ((inventory.at(i).getPriceTier())+5)*10 << " GC" << endl;
        counter++;
    }
    cout << left << counter << left << ". ";
    cout << setw(40) << left << "Sell my stuff!" << endl;
    counter++;
    cout << left << counter << left << ". ";
    cout << setw(40) << left << "Repair your ship's hull";
    cout << (HealthCap - CurrHealth) * 2 << " GC" << endl;
    counter++;
    cout << left << counter << left << ". ";
    cout << setw(25) << left << "Quit Menu" << endl << endl;

    return counter;
}

int PrintSellOptions(vector<Weapon> inventory) {
    int counter = 1;
    int sellPrice;
    cout << setw(40);
    cout << left << "\n\nItem";
    cout << right << "Sale Price" << endl;
    for (int i = 0; i < inventory.size() - 1; i++) {
        cout << left << counter << left << ". ";
        cout << setw(40) << left << inventory.at(i).getWepName();
        sellPrice = inventory.at(i).getPriceTier();
        sellPrice += 5;
        sellPrice *= 10;
        sellPrice = floor(sellPrice*.6);
        cout << sellPrice << " GC" << endl;
        counter++;
    }
    cout << left << counter << left << ". ";
    cout << setw(40) << left << "Buy more stuff!" << endl;
    counter++;
    cout << left << counter << left << ". ";
    cout << setw(25) << left << "Quit Menu" << endl << endl;

    return counter;
}
