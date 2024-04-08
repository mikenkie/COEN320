/*
 * Radar.h
 *
 *  Created on: Apr 5, 2024
 *      Author: matth
 */

#ifndef RADAR_H_
#define RADAR_H_
#include "Aircraft.h"
#include <vector>
#include <pthread.h>

using namespace std;

extern bool radar_active;

class Radar {
	vector<Aircraft*> aircraftList;
	int m[10][10]={0};
	pthread_mutex_t mutex;


public:
	Radar(vector<Aircraft*> acList);
	Radar();

	void simulate();

	virtual ~Radar();

	vector <Aircraft*> getAircraftVector();

};
#endif /* RADAR_H_ */

