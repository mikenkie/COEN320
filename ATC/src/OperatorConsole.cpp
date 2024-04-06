/*
* OperatorConsole.cpp
*
* Author mikenkie
*/

#include "OperatorConsole.h"
#include <string>
#include <iostream>
#include <istream>

OperatorConsole::OperatorConsole(){}

OperatorConsole::OperatorConsole(Aircraft ar): aircraft(ar){}

void OperatorConsole:: requestAircraftControlChange (Aircraft ar) {
    aircraft = ar;
    std::cout << "Aircraft ID: " << aircraft.getId() << " successfully switched to console." << std::endl;
}

Aircraft OperatorConsole:: getAircraftConsole () const {
    return aircraft;
}

void OperatorConsole:: changeSpeedX(ComputerSystem& comSystem, float speedX) {
    string message = "CHANGE SPEEDX ";
    message += to_string(speedX);
    comSystem.send(aircraft, message);
}

void OperatorConsole:: changeSpeedY(ComputerSystem& comSystem, float speedY) {
    string message = "CHANGE SPEEDY ";
    message += to_string(speedY);
    comSystem.send(aircraft, message);
}

void OperatorConsole:: changeSpeedZ(ComputerSystem& comSystem, float speedZ) {
    string message = "CHANGE SPEEDZ ";
    message += to_string(speedZ);
    comSystem.send(aircraft, message);
}

void OperatorConsole:: changePositionX(ComputerSystem& comSystem, float posX) {
    string message = "CHANGE POSX ";
    message += to_string(posX);
    comSystem.send(aircraft, message);
}

void OperatorConsole:: changePositionY(ComputerSystem& comSystem, float posY) {
    string message = "CHANGE POSY ";
    message += to_string(posY);
    comSystem.send(aircraft, message);
}

void OperatorConsole:: changePositionZ(ComputerSystem& comSystem, float posZ) {
    string message = "CHANGE POSZ ";
    message += to_string(posZ);
    comSystem.send(aircraft, message);
}

void OperatorConsole:: sendAugmentedInfoToRadar(ComputerSystem& comSystem) {
    std::string requestAircraftChange;
    int aircraftID; 

    std::cout << "You are currently requesting information about Aircraft " << aircraft.getId() << ". " << std::endl;

    std::cout << "If you wish to change the aircraft to be display on the radar, enter yes or no:"<< std::endl;
    std::cin >> requestAircraftChange;

    // The if statement changes the aircraft the controller wishes to request to be on the rader via send() in Communication System
    if (requestAircraftChange.compare("yes")) {
        std::cout << "Please enter a valid Aircraft ID:" << std::endl;
        std::cin >> aircraftID;

        for (Aircraft* ar: comSystem.getAircraftVectorFromRadar()) {
            if (ar->getId() == aircraftID) {
                requestAircraftControlChange(*ar);
                break;
            }
        }
    }

    comSystem.send(aircraft, "RETRIEVE ALL AIRCRAFT INFORMATION");
    
}