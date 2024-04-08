/*
* OperatorConsole.cpp
*
* Author mikenkie
*/

#include "OperatorConsole.h"
#include <string>
#include <iostream>
#include <istream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "cTimer.h"
#include <string.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>


OperatorConsole::OperatorConsole(){
	pthread_mutex_init(&mutex, NULL);
}

OperatorConsole::OperatorConsole(Aircraft ar): aircraft(ar){
	pthread_mutex_init(&mutex, NULL);
}

void OperatorConsole:: requestAircraftControlChange (Aircraft ar) {
    aircraft = ar;
    std::cout << "Aircraft ID: " << aircraft.getId() << " successfully switched to console." << std::endl;
}

Aircraft OperatorConsole:: getAircraftConsole () const {
    return aircraft;
}


void OperatorConsole:: operator_console_request() {
	my_data_t myData;
	int period_sec = 1;
	cTimer timer(period_sec, 0); //initialize, set, and start the timer

	int time = 0;
	int count = 0;
	string request;

	while (true) {
		time = count * period_sec;

		if (time % 20 == 0) {
			pthread_mutex_lock(&mutex);

			cout << "Do you wish to access operator console? (yes or no)" << endl;
			cin >> request;

			if (request.compare("yes") == 0)
				sporadic_task();

			pthread_mutex_unlock(&mutex);
		}

		count++;
		timer.waitTimer();
		} //end_while
}

void OperatorConsole::sporadic_task() {
	my_data_t myData;
	cout << "From the options below type which you would like to change: \n"
		 << "POSX\n"<< "POSY\n" <<"POSZ\n" << "SPEEDX\n" << "SPEEDY\n" << "SPEEDZ\n" << "SEND INFO TO RADAR"<<endl;
	cin >> myData.command;

	printf("DEBUG MESSAGE: ", myData.command);

	cout << "Enter value:" << endl;
	cin >> myData.data;

	printf("DEBUG MESSAGE: ", myData.data);

	printf("Operator Console retrieving your data inputs: ", myData.command, " ", myData.data, " ....");
	if (myData.command.compare("POSX") == 0) {
		aircraft.setX(myData.data);
	}
	else if (myData.command.compare("POSY") == 0) {
		aircraft.setY(myData.data);
	}
	else if (myData.command.compare("POSZ") == 0) {
		aircraft.setZ(myData.data);
	}
	else if (myData.command.compare("SPEEDX") == 0) {
		aircraft.setSpeedX(myData.data);
	}
	else if (myData.command.compare("SPEEDY") == 0) {
		aircraft.setSpeedY(myData.data);
	}
	else if (myData.command.compare("SPEEDZ") == 0) {
		aircraft.setSpeedZ(myData.data);
	}
	else if (myData.command.compare("SEND INFO TO RADAR") == 0) {
		aircraft.printStatus();;
	}

}
    
