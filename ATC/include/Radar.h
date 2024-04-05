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
using namespace std;

class Radar {
	vector<Aircraft*> aircraftList;
public:
	Radar(vector<Aircraft*> acList);

	void simulate();

	virtual ~Radar();
};
#endif /* RADAR_H_ */

