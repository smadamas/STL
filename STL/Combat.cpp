#pragma once
#include <iostream>
#include "Combat.h"
#include <chrono>
#include <thread>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

//Return value is victory or not
bool startCombat(Ship* x, Ship* y) {
    vector<Weapon> yourWeps = x->getWeapons();
    vector<Weapon> theirWeps = y->getWeapons();
    int answer;
    int wepAnswer;
    int wepCounter = 1;
    bool cycleTurn = true;
    bool evasionBoost = false;
    bool enemyMoved = false;


    //yourWeps[0].setStatus("shitty");

    while (true) {
        while (cycleTurn) {
            //Fight Interface
            cout << "\nWhat will you do?!? Enter a corresponding number. View your weapons by entering 99!" << endl;
            cout << setw(20) << left << "\nYour Health: " << x->getShipHealth() << " / " << x->getShipHealthCap();
            cout << setw(20) << "   Enemy Health: " <<  y->getShipHealth() << " / " << y->getShipHealthCap() << endl;
            cout << setw(20) << left << "Your Shield: " <<  x->getSheildHealth() << " / " << left << x->getShieldCap();
            cout << setw(20) << "   Enemy Shield: " << y->getSheildHealth() << " / " << left << y->getShieldCap() << endl;

            cout << "\nOptions: " << endl;
            wepCounter = 1;
            for (int i = 0; i <= yourWeps.size()-1; i++) {
                cout << wepCounter << ". " << yourWeps[i].getStatus() << " " << yourWeps[i].getWepName() << endl;
                wepCounter++;
            }
            cout << wepCounter << ". " << "Evasive maneuver (increase evasion for this turn)" << endl;
            wepCounter++;
            cout << wepCounter << ". " << "Repair shields!" << endl;
            wepCounter++;
            cout << wepCounter << ". " << "Try to fly away!" << endl;

            cin >> answer;
            if (answer < wepCounter - 2) {
                cout << "\nWhat do you want to with this weapon? Enter a number." << endl;
                cout << "1. Charge/Fire" << endl;
                cout << "2. Cancel charge" << endl;
                cout << "3. Discard (increase evasion permanently!)" << endl;
                cout << "4. Exit this wepon's menu" << endl;

                cin >> wepAnswer;
                if (wepAnswer == 1) {
                    if (yourWeps[answer - 1].getStatus() == "(dormant)") {
                        yourWeps[answer - 1].setStatus("(charging)");
                        cycleTurn = false;
                    }
                }
                else if (wepAnswer == 2) {
                    yourWeps[answer - 1].setStatus("(dormant)");
                }
                else if (wepAnswer == 3){
                    yourWeps.erase(yourWeps.begin() + answer - 1);
                    x->setEvasion(x->getEvasion() * 1.4);
                    cycleTurn = false;
                }
            }
            else if (answer == 99) {
                cout << endl;
                x->getWepSet();
                cin.ignore();
                cin >> answer;
            }
            else {
                cycleTurn = false;
            }
        }

        //Modifiers and menu option execution besides attack
        if (answer == wepCounter) {
            if (x->getEvasion() > 2*(y->getEvasion())) {
                cout << "\nDodging some attacks on your way out, you managed to escape! Well done. Onto the next location..." << endl;
                return true;
            }
            else {
                cout << "\nYou attepted to escape but were not fast enough and the enemy traps you in..." << endl;
            }
        }
        else if (answer == wepCounter - 1) {
            x->setSheildHealth(x->getSheildHealth() + 2);
            cout << "\nYou mess with your defense controls and are able to regenerate two extra hitpoints on your shield just in time!" << endl;
        }
        else if (answer == wepCounter - 2) {
            cout << "\nYou pull off a sick evasive maneuver in an attept to dodge your enemy's attacks for the turn." << endl;
            evasionBoost = true;
            x->setEvasion(x->getEvasion()*(3/2));
        }


        //Execution of enemy attack choice
        for (int i = 0; i < theirWeps.size(); i++) {
            if (theirWeps[i].getStatus() == "(dormant)") {
                theirWeps[i].setStatus("(charging)");
                enemyMoved = true;
                break;
            }
        }
        if (!enemyMoved) {
            y->setSheildHealth(y->getSheildHealth()+2);
            enemyMoved = false;
        }

        //Countdowns and attacks
        int calc;
        int evadeRatio;
        int disableCalc;
        for (int i = 0; i < yourWeps.size(); i++) {
            
            //Disable Countdown
            if (yourWeps[i].getStatus() == "(disabled)") {
                yourWeps[i].setDisabledTurns(yourWeps[i].getDisabledTurns() - 1);
                if (yourWeps[i].getDisabledTurns() == 0) {
                    yourWeps[i].setStatus("(dormant)");
                }

            }
            
            //Charge
            if (yourWeps[i].getStatus() == "(charging)" && yourWeps[i].getChrTurns() != 0) {
                yourWeps[i].setChrTurns(yourWeps[i].getChrTurns() - 1);
            }
            else if (yourWeps[i].getStatus() == "(charging)" && yourWeps[i].getChrTurns() == 0) {
                //FIRE!!!

                cout << x->getShipName() << "'s " << yourWeps[i].getWepName() << " fired!" << endl;
                sleep_for(1s);

                //Goes through evasion?
                evadeRatio = rand() % 20 + 1;
                if (evadeRatio > y->getEvasion()) {

                    cout << y->getShipName() << " was hit by " << yourWeps[i].getWepName() << "!" << endl;
                    sleep_for(1s);
                    //Damage shield and hull
                    if (y->getSheildHealth() > 0) {
                        y->setSheildHealth(y->getSheildHealth()- yourWeps[i].getDamage());
                        calc = y->getSheildHealth();
                        if (calc < 0) {
                            y->setShipHealth(y->getShipHealth() - abs(calc));
                            y->setSheildHealth(0);
                        }
                        
                    }
                    else {
                        y->setShipHealth(y->getShipHealth() - yourWeps[i].getDamage());
                    }

                    //Disable weapon
                    if (yourWeps[i].getDISABLETurns() > 0) {
                        disableCalc = round(rand() % theirWeps.size() + 1);
                        theirWeps[disableCalc - 1].setDisabledTurns(yourWeps[i].getDISABLETurns());
                        theirWeps[disableCalc - 1].setStatus("(disabled)");
                    }

                    //Check enemy death
                    if (y->getShipHealth() <= 0) {
                        return true;
                    }
                }
                else {
                    cout << "Shot missed!" << endl;
                }

                //Reset charge time to empty charge
                yourWeps[i].setChrTurns(yourWeps[i].getChrTime());
                yourWeps[i].setStatus("(dormant)");
            }
        }
        for (int i = 0; i < theirWeps.size(); i++) {

            //Disable Countdown
            if (theirWeps[i].getStatus() == "(disabled)") {
                theirWeps[i].setDisabledTurns(theirWeps[i].getDisabledTurns() - 1);
                if (theirWeps[i].getDisabledTurns() == 0) {
                    theirWeps[i].setStatus("(dormant)");
                }

            }

            //Charge
            if (theirWeps[i].getStatus() == "(charging)" && theirWeps[i].getChrTurns() != 0) {
                theirWeps[i].setChrTurns(theirWeps[i].getChrTurns() - 1);
            }
            else if (theirWeps[i].getStatus() == "(charging)" && theirWeps[i].getChrTurns() == 0) {
                //FIRE!!!

                cout << y->getShipName() << "'s " << theirWeps[i].getWepName() << " fired by enemy..." << endl;
                sleep_for(1s);

                //Goes through evasion?
                evadeRatio = rand() % 20 + 1;
                if (evadeRatio > x->getEvasion()) {
                    cout << x->getShipName() << " was hit by " << theirWeps[i].getWepName() << "!" << endl;
                    sleep_for(1s);

                    //Damage shield and hull
                    if (x->getSheildHealth() > 0) {
                        x->setSheildHealth(x->getSheildHealth() - theirWeps[i].getDamage());
                        calc = x->getSheildHealth();
                        if (calc < 0) {
                            x->setShipHealth(x->getShipHealth() - abs(calc));
                            x->setSheildHealth(0);
                        }
                        
                    }
                    else {
                        x->setShipHealth(x->getShipHealth() - theirWeps[i].getDamage());
                    }

                    //Disable weapon
                    if (theirWeps[i].getDISABLETurns() > 0) {
                        disableCalc = round(rand() % theirWeps.size() + 1);
                        yourWeps[disableCalc - 1].setDisabledTurns(theirWeps[i].getDISABLETurns());
                        yourWeps[disableCalc - 1].setStatus("(disabled)");
                    }

                    //Check enemy death
                    if (x->getShipHealth() <= 0) {
                        return false;
                    }
                }
                else {
                    cout << "Shot missed!" << endl;
                }

                //Reset charge time to empty charge
                theirWeps[i].setChrTurns(theirWeps[i].getChrTime());
                theirWeps[i].setStatus("(dormant)");
            }
        }

        if (evasionBoost) { x->setEvasion(x->getEvasion() * (2/3)); }
        sleep_for(1s);
        cycleTurn = true;
    }
    return true;
}