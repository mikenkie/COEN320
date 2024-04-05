/*
* OperatorConsole.cpp
*
* Author mikenkie
*/

#include "OperatorConsole.h"
#include "Radar.h"

OperatorConsole::OperatorConsole() {}

OperatorConsole::OperatorConsole(Aircraft ar) {
    aircraft = ar;
}

void OperatorConsole:: requestAircraftControlChange (Aircraft ar) {
    aircraft = ar;
    std::cout << "Aircraft ID: " << aircraft.getId() << " successfully switched to console." << std::endl;
}

Aircraft OperatorConsole:: getAircraftById(int requestedID) {
    int temp;
    for (int i = 0; i < 5; i++) {
        temp = arrayAircrafts->getId()
        if (temp == requestedID) {
            return arrayAircrafts[i];
        }
    }
    return null; 
}
Aircraft OperatorConsole:: getAircraftConsole () const {
    return aircraft;
}

void OperatorConsole:: changeSpeedX(float speedX) {
    aircraft.setSpeedX(speedX); 
}

void OperatorConsole:: changeSpeedY(float speedY) {
    aircraft.setSpeedY(speedY); 
}

void OperatorConsole:: changeSpeedZ(float speedZ) {
    aircraft.setSpeedZ(speedZ); 
}

void OperatorConsole:: changePositionX(float posX) {
    aircraft.setX(posX);
}

void OperatorConsole:: changePositionY(float posY) {
     aircraft.setY(posY);
}

void OperatorConsole:: changePositionZ(float posZ) {
     aircraft.setZ(posZ);
}

void OperatorConsole:: sendAugmentedInfoToRadar(std::string message) {
    std::cout << "You are currently requesting information about Aircraft " << aircraft.getId() << ". " << std::endl;

    std::cout << "If you wish to change the aircraft to be display on the radar, enter yes or no:"<< std::endl;
    std::cin >> requestAircraftChange;

    // The if statement changes the aircraft the controller wishes to request to be on the rader
    if (requestAircraftChange.compare("yes")) {
        std::cout << "Please enter a valid Aircraft ID:" << std::endl;
        std::cin >> aircraftID;

        requestAircraftControlChange();
    }
    else {

    }
}