#pragma once
#include <iostream>
#include <memory>
#include <iomanip>
#include <vector>
#include <string>
#include "RandomEvents.h"
#include "Weapon.h"
#include "Ship.h"
#include <chrono>
#include <thread>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds



int main() {

    /*int getEventCode(int EventCode);
    int getNewEventCode(int EventCode);
    int getNextEvent(Ship PlayerShip, int EventCode, int galaxy, int galacticCredits);*/

    //Beginning code, collect name
    string playerName;
    char nameAnswer;
    //cout << "                          WELCOME TO STL!" << endl;
    cout << R"(____    __    ____  _______  __        ______   ______   .___  ___.  _______    .___________.  ______           _______.___________. __  )" << endl;
    cout << R"(\   \  /  \  /   / |   ____||  |      /      | /  __  \  |   \/   | |   ____|   |           | /  __  \         /       |           ||  |
)";
    cout << R"( \   \/    \/   /  |  |__   |  |     |  ,----'|  |  |  | |  \  /  | |  |__      `---|  |----`|  |  |  |       |   (----`---|  |----`|  |
)";
    cout << R"(  \            /   |   __|  |  |     |  |     |  |  |  | |  |\/|  | |   __|         |  |     |  |  |  |        \   \       |  |     |  |
)";
    cout << R"(   \    /\    /    |  |____ |  `----.|  `----.|  `--'  | |  |  |  | |  |____        |  |     |  `--'  |    .----)   |      |  |     |  `----.
)";
    cout << R"(    \__/  \__/     |_______||_______| \______| \______/  |__|  |__| |_______|       |__|      \______/     |_______/       |__|     |_______|
)" << endl << endl;
    cout << "                      A journey through space" << endl << endl;



    bool run = true;
    do {
        cout << "\nPlease enter your name: " << endl;
        getline(cin, playerName);
        cout << "Your name is " << playerName << "? Type Y or N." << endl;
        cin >> nameAnswer;

        if (nameAnswer == 'Y' || nameAnswer == 'y') {
            run = false;
        }
        else if (nameAnswer == 'N' || nameAnswer == 'n') {
            cout << "Ok, let's start over." << endl;
            cin.ignore();
            cin.clear();
        }
    } while (run);

    //Choose your ship
    cout << "\nTime to choose a spaceship! Your options are..." << endl;
    cout << "Key: Base Power - used to run weapons and shields on your ship\nEvasion - helps you dodge attacks\nWeapons capacity - each ship has a certain number of slots to mount weapons" << endl;
    cout << "\nA. THE CRUISER" << endl;
    cout << "Base power: 11" << endl;
    cout << "Evasion: 5" << endl;
    cout << "Hit Points: 21" << endl;
    cout << "Weapons capacity: 4" << endl;
    cout << "Color: beige" << endl;
    cout << "\nB. THE HOT ROD" << endl;
    cout << "Base power: 8" << endl;
    cout << "Evasion: 10" << endl;
    cout << "Hit Points: 10" << endl;
    cout << "Weapons capacity: 2" << endl;
    cout << "Color: cherry red" << endl;
    cout << "\nC. THE ALIEN STARSHIP" << endl;
    cout << "Base power: 14" << endl;
    cout << "Evasion: 8" << endl;
    cout << "Hit Points: 15" << endl;
    cout << "Weapons capacity: 3" << endl;
    cout << "Color: lime green" << endl;
    cout << "\nEnter a character corresponding to your choice!" << endl;
    char playerShipType;

    //Take input for ShipType
    run = true;
    do {
        cin >> playerShipType;

        if (playerShipType == 'A' || playerShipType == 'B' || playerShipType == 'C') {
            run = false;
        }
        else {
            cout << "\nTry again you asshat. You were supposed to enter A, B or C. DO IT!" << endl;
        }
    } while (run);


    //Name your ship
    string playerShipName;
    nameAnswer = 'A';
    cin.ignore();

    run = true;
    do {
        cout << "Great! How about giving your lovely starcraft a name? Write anything and press enter.\nSpaceship name: " << endl;
        getline(cin, playerShipName);
        cout << "You're gonna name your ship " << playerShipName << "? Type Y or N." << endl;
        cin >> nameAnswer;

        if (nameAnswer == 'Y' || nameAnswer == 'y') {
            run = false;
        }
        else if (nameAnswer == 'N' || nameAnswer == 'n') {
            cout << "Ok, let's start over." << endl;
            cin.ignore();
            cin.clear();
        }
    } while (run);

    //Initialization of the player ship
    Ship playerShip = Ship(playerShipType, playerShipName);

    cout << "Just so we're clear, here's your stats at the beginning of your journey." << endl;
    cout << "Health: " << playerShip.getShipHealth() << endl;
    cout << "Ship name: " << playerShip.getShipName() << endl;
    cout << "Ship color: " << playerShip.getShipColor() << endl;
    cout << "Power: " << playerShip.getPower() << endl;
    cout << "Evasion: " << playerShip.getEvasion() << endl;
    cout << "Weapon capacity: " << playerShip.getWepCapacity() << endl;
    cout << "Weapons List: " << endl;
    playerShip.getWepSet();
    cout << endl;
    cout << "\nBefore you start an event, you can view these stats anytime by typing: \"I\" instead of your navigation selection.\n" << endl;

    cin.ignore();
    cout << "\n\nPress Enter to continue!" << endl;
    cin.ignore();

    cout << "Here's the situation: you are a leader of the rebel resistance to a foreign occupation of" << endl;
    cout << "your star system. There are 3 galaxies, and you'll need to clean each of the rebel scum within," << endl;
    cout << "but be ready! You must also fight the The Dread Son, first of his name, last of the ungodly," << endl;
    cout << "the unburnt, who rules with an Iron Boot. Sure, your aren't ready now, but you'll accumulate" << endl;
    cout << "everything you need throughout your journey through your star system! (if all goes well). Watch" << endl;
    cout << "out for pirates, rebels, and monsters while you're out there! And best of luck. If you're looking" << endl;
    cout << "for advice between turns during an event, type \"HELP\" and I'll try to give some advice!" << endl;

    cout << "\n\nPress Enter to continue!" << endl;
    cin.ignore();

    //Let's make sure you're repesented as existing still
    bool alive = true;
    int galaxy = 1;
    bool Win;
    int EventCode = 999;
    bool skipGalaxy = false;
    int galacticCredits = 100;
    int *gcPoint = &galacticCredits;

    do {
        if (galaxy == 1) {

            //Intro to galaxy 1
            cout << endl << "Ok, your journey is about to begin. You will be presented with random encounters as you advance" << endl;
            cout << "through the three galaxies, each more difficult than the last as you approach The" << endl;
            cout << "Dread Son. Find as many shops as you can to upgrade your weapons and fix your ship!" << endl;

            cout << endl << "You are approaching the first galaxy. Prepare yourself!" << endl;
            //sleep_for(3s);
            cout << "Outer rings located..." << endl;
            //sleep_for(3s);            
            cout << "Honing toward outermost planet..." << endl;
            //sleep_for(7s);
            cout << "Auto-navigating through asteroid belt..." << endl;
            //sleep_for(7s);
            cout << "Engaging with planet telecommunications..." << endl;
            //sleep_for(3s);

            for (int i = 1; i <= 8; i++) {
                EventCode = getNewEventCode();
                alive = getNextEvent(&playerShip, EventCode, galaxy, gcPoint);
                if (alive == false || skipGalaxy) {
                    break;
                }

            }

        }
        else if (galaxy == 2) {
            //Intro to gal 2
            cout << endl << "Wow! Some close calls in there, but you handled it like a champ!" << endl;
            cout << "Let's hope you saved your mettle for this next challenge. I have faith in you!" << endl;

            for (int i = 1; i <= 8; i++) {
                EventCode = getNewEventCode();
                alive = getNextEvent(&playerShip, EventCode, galaxy, gcPoint);
                if (alive == false || skipGalaxy) {
                    break;
                }

            }
        }
        else if (galaxy == 3) {
            //Intro to gal 3
            cout << endl << "You're officially the superstar rebel of the sector! But there's no time to celebrate now..." << endl;
            cout << "The Dread Son knows of you, and is on his way to strike you down before the rebellion comes to fruition!" << endl;
            cout << "This will be you biggest challenge yet. Use your resources wisely and fly carefully..." << endl;

            for (int i = 1; i <= 8; i++) {
                EventCode = getNewEventCode();
                alive = getNextEvent(&playerShip, EventCode, galaxy, gcPoint);
                if (alive == false) {
                    break;
                }

            }
        }

        galaxy++;
    } while (alive && galaxy < 4);

    //Died during a galaxy
    if (!alive) {
        cout << endl << "Tough break! Seems you weren't the leader we needed in these desperate times. RIP the rebellion..." << endl;
        cout << "Reload this code to try out the challenge in an alternate universe, but know that this one is SCREWED." << endl;
    }
    return 0;
}
