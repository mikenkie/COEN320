/*
 * System.h
 *
 *  Created on: Apr 7, 2024
 *      Author: matth
 */

#ifndef SRC_SYSTEM_H_
#define SRC_SYSTEM_H_
#include "Aircraft.h"
#include <vector>
#include "Radar.h"
#include "OperatorConsole.h"


class System {
private:
	vector<Aircraft*> aircraftList;
	Radar* radar;
	OperatorConsole* opCon;

	// This is used to generate data of aircrafts from input file
	typedef struct _my_aircraft {
		int entrancetime;
		int ID;
		float coordx, coordy, coordz;
		float speedx, speedy, speedz;
	} my_aircraft_t;

public:
	System();
	System(vector<Aircraft*> acList, Radar* r, OperatorConsole* oc);
	virtual ~System();
	void simulate();
	void read_aircrafts_from_input_file();
};

#endif /* SRC_SYSTEM_H_ */
