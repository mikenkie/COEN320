/*
 * ComputerSystem.h
 *
 *  
 * Author: mikenkie
 */
#ifndef COMPUTERSYSTEM_H_
#define COMPUTERSYSTEM_H_

#include <iostream>
#include <Aircraft.h>
#include <CommunicationSystem.h>
#include <DataDisplay.h>
#include <OperatorConsole.h>
#include <Radar.h>

class ComputerSystem {
    private:
        CommunicationSystem communicationSystem;
        DataDisplay dataDisplay;
        Radar radar;
        OperatorConsole opConsole;

    public:
        ComputerSystem();
        ComputerSystem(CommunicationSystem& comSystem, Radar& radar, OperatorConsole& opConsole, DataDisplay& display);

        // Method responsible for the transmission of controller commands to the specified aircraft
        void send (Aircraft& aircraft, std::string message);

        vector <Aircraft*> getAircraftVectorFromRadar();

};

#endif