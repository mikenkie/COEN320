/*
 * Aircraft.cpp
 *
 *  Created on: Apr 2, 2024
 *      Author: matth
 */

#include "Aircraft.h"

#include <unistd.h> // For sleep()
// Constructor implementation
Aircraft::Aircraft(int id, float posX, float posY, float posZ, float sX,
		float sY, float sZ) :
		id(id), x(posX), y(posY), z(posZ), speedX(sX), speedY(sY), speedZ(sZ) {
}

Aircraft::Aircraft(int id) :
		id(id), x(0), y(0), z(0), speedX(0), speedY(0), speedZ(0) {
}

// Get/set
int Aircraft::getId() const {
	return id;
}
float getX() const {
	return x;
}
float getY() const {
	return y;
}

// Update position based on speed and elapsed time
void Aircraft::updatePosition(float deltaTime) {
	x += speedX * deltaTime;
	y += speedY * deltaTime;
	z += speedZ * deltaTime;
}

// Print current status of the aircraft
void Aircraft::printStatus() const {
	std::cout << "Aircraft ID: " << id << " - Position: (" << x << ", " << y
			<< ", " << z << ") Speed: (" << speedX << ", " << speedY << ", "
			<< speedZ << ")" << std::endl;
}

void Aircraft::simulate() {

	for (int i = 0; i < 5; ++i) {
		x += speedX; // Update x coordinate
		y += speedY; // Update y coordinate
		std::cout << "Aircraft " << id << " is operating at coordinates (" << x
				<< ", " << y << ", " << z << ")" << std::endl;
		sleep(1); // Sleep for a bit to simulate time passing
	}
}
