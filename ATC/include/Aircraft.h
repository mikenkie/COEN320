/*
 * Aircraft.h
 *
 *  Created on: Apr 2, 2024
 *      Author: matth
 */

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include <iostream>
#include <unistd.h> // For sleep()

class Aircraft {
private:
	int id;
	float x, y, z; // Position coordinates
	float speedX, speedY, speedZ; // Speed components in each direction

public:

	// Constructor
	Aircraft(int id, float posX, float posY, float posZ, float speedX, float speedY, float speedZ);
	Aircraft(int id);

	// Getter for ID
	int getId() const;
	float getY() const;
	float getX() const;

	// Method to update the position based on speed and elapsed time
    void updatePosition(float deltaTime);

    // Method to print the current position and speed of the aircraft
    void printStatus() const;

    void simulate();
};

#endif /* AIRCRAFT_H_ */
