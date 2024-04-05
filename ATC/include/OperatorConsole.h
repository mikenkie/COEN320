/*
 * OperatorConsole.h
 *
 *  
 * Author: mikenkie
 */
#ifndef OPERATORCONSOLE_H_
#define OPERATORCONSOLE_H_

#include <iostream>
#include "Aircraft.h"

class OperatorConsole {
    private:
        Aircraft aircraft;
        Aircraft arrayAircrafts [5];

    public:
        // Constructor
        OperatorConsole();
        OperatorConsole(Aircraft ar);

        // Method to allow controller to change which aircraft they wish to control
        void requestAircraftControlChange (Aircraft ar);
        Aircraft getAircraftConsole () const;
        Aircraft getAircraftById(int requestedID);

        // Methods to allow the controller to change speed of the desired aircraft. 
        void changeSpeedX(float speedX);
        void changeSpeedY(float speedY);
        void changeSpeedZ(float speedZ);

        // Methods to allow the controller to change position's coordinates of the desired aircraft. 
        void changePositionX(float posX);
        void changePositionY(float posY);
        void changePositionZ(float posZ); // reminder: flight level

        // Method to send information about aircraft to Radar to be displated by DataDisplay
        void sendAugmentedInfoToRadar( std::string message);


};

#endif