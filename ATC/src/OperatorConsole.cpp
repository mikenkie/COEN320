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


OperatorConsole::OperatorConsole(){}

OperatorConsole::OperatorConsole(Aircraft ar): aircraft(ar){}

void OperatorConsole:: requestAircraftControlChange (Aircraft ar) {
    aircraft = ar;
    std::cout << "Aircraft ID: " << aircraft.getId() << " successfully switched to console." << std::endl;
}

Aircraft OperatorConsole:: getAircraftConsole () const {
    return aircraft;
}

/*
 * Creates the channel to initiate connection with ATC. User inputs command and value. This is the message
 * being passed. It sends the message to the receiver at the end of the channel
 */
void OperatorConsole:: operator_console_start_routine() {
	my_data_t myData;

	cout << "From the options below type which you would like to change: \n"
		 << "POSX\n "<< "POSY\n" <<"POSZ\n" << "SPEEDX\n" << "SPEEDY\n" << "SPEEDZ\n" << "SEND INFO TO RADAR"<<endl;
	cin >> myData.command;

	cout << "Enter value:" << endl;
	cin >> myData.data;

	int server_coid; //server connection ID.

	if ((server_coid = name_open(ATTACH_POINT, 0)) == -1) {
		perror("Error occurred while attaching the channel");
	}

	printf("DEBUG: Starting to send request to ATC...");
	if (MsgSend(server_coid, &myData, sizeof(myData), NULL, 0) == -1) {
				printf("Error while sending the data message");
	}


	/* Close the connection */
	name_close(server_coid);
}
    
