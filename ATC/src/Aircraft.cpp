/*
 * Aircraft.cpp
 *
 *  Created on: Apr 2, 2024
 *      Author: matth
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#include "cTimer.h"
#include "Aircraft.h"

#include <unistd.h> // For sleep()
// Constructor implementation

Aircraft::Aircraft(int id, float posX, float posY, float posZ, float sX,
		float sY, float sZ) {
	this->id = id;
	this->x = posX;
	this->y = posY;
	this->z = posZ;
	this->speedX = sX;
	this->speedY = sY;
	this->speedZ = sZ;
	pthread_mutex_init(&mutex, NULL); // Initialize the mutex
}

Aircraft::Aircraft(int id) :
		id(id), x(0), y(0), z(0), speedX(0), speedY(0), speedZ(0) {
}

Aircraft::Aircraft() {
}

// Get/set
int Aircraft::getId() const {
	return id;
}
float Aircraft::getX() const {
	return x;
}
float Aircraft::getY() const {
	return y;
}

void Aircraft::setX(float posX) {
	x = posX;
}

void Aircraft::setY(float posY) {
	y = posY;
}

void Aircraft::setZ(float posZ) {
	z = posZ;
}

void Aircraft::setSpeedX(float spX) {
	speedX = spX;
}

void Aircraft::setSpeedY(float spY) {
	speedY = spY;
}

void Aircraft::setSpeedZ(float spZ) {
	speedZ = spZ;
}

// Print current status of the aircraft
void Aircraft::printStatus() const {
	std::cout << "Aircraft ID: " << id << " - Position: (" << x << ", " << y
			<< ", " << z << ") Speed: (" << speedX << ", " << speedY << ", "
			<< speedZ << ")" << std::endl;
}

void Aircraft::simulate() {
	int period_sec = 1;
	cTimer timer(period_sec, 0); //initialize, set, and start the timer

	int time = 0;
	int count = 0;

	while (true) {
		time = count * period_sec;

		x = speedX * (time);
		y = speedY * (time);
		z = speedZ * (time);

		count++;
		timer.waitTimer();
	} //end_while
}

void Aircraft::radarResponse(int &idOut, float &xOut, float &yOut, float &zOut,
		float &sXOut, float &sYOut, float &sZOut) {
	idOut = id;
	xOut = x;
	yOut = y;
	zOut = z;
	sXOut = speedX;
	sYOut = speedY;
	sZOut = speedZ;
}
