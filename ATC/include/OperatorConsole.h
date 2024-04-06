/*
 * OperatorConsole.h
 *
 *  
 * Author: mikenkie
 */
#ifndef OPERATORCONSOLE_H_
#define OPERATORCONSOLE_H_

#include <iostream>
#include <istream>
#include "Aircraft.h"
#include "ComputerSystem.h"

class OperatorConsole {
    private:
        Aircraft aircraft;

    public:
        // Constructor
        OperatorConsole();
        OperatorConsole(Aircraft ar);

        // Method to allow controller to change which aircraft they wish to control
        void requestAircraftControlChange (Aircraft ar);
        Aircraft getAircraftConsole () const;

        // Methods to allow the controller to change speed of the desired aircraft. 
        void changeSpeedX(ComputerSystem& comSystem, float speedX);
        void changeSpeedY(ComputerSystem& comSystem, float speedY);
        void changeSpeedZ(ComputerSystem& comSystem, float speedZ);

        // Methods to allow the controller to change position's coordinates of the desired aircraft. 
        void changePositionX(ComputerSystem& comSystem, float posX);
        void changePositionY(ComputerSystem& comSystem, float posY);
        void changePositionZ(ComputerSystem& comSystem, float posZ); // reminder: flight level

        // Method to send information about aircraft to Radar to be displated by DataDisplay
        void sendAugmentedInfoToRadar(ComputerSystem & comSysteme);


};

#endif