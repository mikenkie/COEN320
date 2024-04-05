/*
 * CommunicationSystem.h
 *
 *  
 * Author: mikenkie
 */

#ifndef COMMUNICATIONSYSTEM_H_
#define COMMUNICATIONSYSTEM_H_

#include <iostream>
#include <string>
#include "Aircraft.h"

class CommunicationSystem {
    private:

    public: 
        // Default Constructor
        CommunicationSystem();

        // Method responsible for the transmission of controller commands to the specified aircraft
        void send (Aircraft aircraft, std::string message);
};

#endif
