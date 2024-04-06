/*
 * Radar.cpp
 *
 *  Created on: Apr 5, 2024
 *      Author: matth
 */

#include "Radar.h"
#include "Aircraft.h"
#include <iostream>
#include <vector>
#include "cTimer.h"
using namespace std;

Radar::Radar(vector<Aircraft*> acList){
	aircraftList = acList;
}

Radar::Radar(){}

Radar::~Radar() {
	// TODO Auto-generated destructor stub
}

vector <Aircraft*> Radar::getAircraftVector() {
	return aircraftList;
}

void Radar::simulate(){
	int period_sec = 1;
	cTimer timer(period_sec, 0); //initialize, set, and start the timer

	int time = 0;
	int count = 0;

	while (true) {
		time = count * period_sec;
		if ((time % 5) == 0) {
			for (Aircraft* aircraft : aircraftList) {
				int id;
				float x, y, z, speedX, speedY, speedZ;
				aircraft->radarResponse(id, x, y, z, speedX, speedY, speedZ);

				 cout << "Aircraft ID: " << id << " - Position: (" << x << ", " << y
						<< ", " << z << ") Speed: (" << speedX << ", " << speedY
						<< ", " << speedZ << ")" << endl;
			}
		}
		count++;
		timer.waitTimer();
	} //end_while
}
;
