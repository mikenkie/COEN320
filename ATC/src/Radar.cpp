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

Radar::Radar(vector<Aircraft*> acList) {
	aircraftList = acList;
}

Radar::Radar() {
}

Radar::~Radar() {
	// TODO Auto-generated destructor stub
}

vector<Aircraft*> Radar::getAircraftVector() {
	return aircraftList;
}

void Radar::simulate() {
	int period_sec = 1;
	cTimer timer(period_sec, 0); //initialize, set, and start the timer

	int time = 0;
	int count = 0;

	while (true) {
		time = count * period_sec;

		if ((time % 5) == 0) {
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 11; j++) {
					m[i][j] = 0;
				}
			}
			for (Aircraft *aircraft : aircraftList) {
				int id;
				float x, y, z, speedX, speedY, speedZ;
				bool active;
				aircraft->radarResponse(id, x, y, z, speedX, speedY, speedZ, active);
				int locX, locY;

				locX = x / 10000;
				locY = y / 10000;
				if (active) {
					if (locX <= 10 && locY <= 10 && locX >= 0 && locY >= 0) {
						if(locX == 10 && locY == 8){
							cout << id;
						}
						m[locY][locX] = m[locY][locX] + 1;
					}
				}
				/*cout << "Aircraft ID: " << id << " - Position: (" << x << ", "
						<< y << ", " << z << ") Speed: (" << speedX << ", "
						<< speedY << ", " << speedZ << ")" << endl;*/
			}
//			for (int i = 0; i < 11; i++) {
//				for (int j = 0; j < 11; j++) {
//					cout << m[i][j] << " ";
//				}
//				cout << " " << endl;
//			}
		}

		count++;
		timer.waitTimer();
	} //end_while
}

void Radar::display() {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			cout << m[i][j] << " ";
		}
		cout << " " << endl;
	}
	cout << "---------------------" << endl;
}
;
