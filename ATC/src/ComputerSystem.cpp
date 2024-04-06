/*
* ComputerSystem.cpp
*
* Author mikenkie
*/

#include "ComputerSystem.h"

ComputerSystem::ComputerSystem() {
}

ComputerSystem:: ComputerSystem(CommunicationSystem& i, Radar& j, OperatorConsole& k, DataDisplay& h){
    this->communicationSystem = i;
    this->radar = j;
    this->opConsole = k;
    this->dataDisplay = h;
}

void ComputerSystem:: send (Aircraft& aircraft, std::string message) {
    
    if (message.compare("RETRIEVE ALL AIRCRAFT INFORMATION") == 0) {
        dataDisplay.displayInfoToRadar (aircraft);
    }
    else {
        // Splits the messafe into command and float value
        size_t lastSpace = message.find_last_of(' ');
        string command = message.substr(0, lastSpace);
        string last_word = message.substr(lastSpace + 1); 
        float value =  stof (last_word);

        if (command.compare("CHANGE POSX") == 0) {
            communicationSystem.executeChangePositionX (aircraft, value);
        }
        else if (command.compare("CHANGE POSY") == 0) {
          communicationSystem.executeChangePositionY (aircraft, value);
        }
        else if (command.compare("CHANGE POSZ") == 0) {
            communicationSystem.executeChangePositionZ (aircraft, value);
        }
        else if (command.compare("CHANGE SPEEDX") == 0) {
            communicationSystem.executeChangeSpeedX(aircraft, value);
        }
        else if (command.compare("CHANGE SPEEDY") == 0) {
            communicationSystem.executeChangeSpeedY(aircraft, value);
        }
        else if (command.compare("CHANGE SPEEDZ") == 0) {
            communicationSystem.executeChangeSpeedZ(aircraft, value);
        }
    }   
}

vector <Aircraft*> ComputerSystem::getAircraftVectorFromRadar() {
	return radar.getAircraftVector();
}