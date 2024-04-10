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

public:
	System();
	System(vector<Aircraft*> acList, Radar* r, OperatorConsole* oc);
	virtual ~System();
	void simulate();
};

#endif /* SRC_SYSTEM_H_ */
