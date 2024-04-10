/*
 * System.cpp
 *
 *  Created on: Apr 7, 2024
 *      Author: matth
 */

#include "System.h"
#include "Aircraft.h"
#include "Radar.h"
#include "OperatorConsole.h"
#include <iostream>
#include <vector>
#include "cTimer.h"
#include <cmath>

// All for reading input file
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

System::System() {
	// TODO Auto-generated constructor stub

}
System::System(vector<Aircraft*> acList, Radar *r, OperatorConsole *oc) {
	aircraftList = acList;
	radar = r;
	opCon = oc;
}

System::~System() {
	// TODO Auto-generated destructor stub
}

void System::read_aircrafts_from_input_file() {
	my_aircraft_t aircraft_values;
	int input_file;
	int size_read;
	char buffer[305]; // Manually adjust the size of the buffer according to the input file
	int index = 0;

	int reset = 1; // The number of lines in text file that defines an aircraft

	/*
	 * Open a file for input but replace file you want to read with the path.
	 * For testing, we have four files: input_low, input_medium, input_high, input_overload.
	 */
	input_file = open( "input_low.txt", O_RDONLY );


    // Read characters from file until end of file is encountered
    while ((size_read = read(input_file, &buffer[index], 1)) > 0) {
    	// If the reader reaches the end of the line, else continues to add character to buffer
        if (buffer[index] == '\n' || index == sizeof(buffer) - 1) {
            // Print content read up to newline character or end of buffer
            buffer[index] = '\0'; // Null-terminate the string
            std::cout << "Line: " << buffer << std::endl; //Debug message

            /* Test for error */
            if( size_read == -1 )
                perror( "Error reading input file." );

            // Extract values
            std::string data;

            int i =0;
            for (i = 0; buffer[i] != '\0'; ++i) {
            	if (buffer[i] == ' ') {
            		break;
            	}
            }

            for (int j = i+1; buffer[j] != '\0'; ++j) {
            	data += buffer[j];
            }

            switch (reset) {
            case 1: // Time
            	aircraft_values.entrancetime = stoi(data);
            	break;
            case 2: // Aircraft ID
            	aircraft_values.ID = stoi(data);
            	break;
            case 3: // X
            	aircraft_values.coordx = stof(data);
            	break;
            case 4: // Y
            	aircraft_values.coordy = stof(data);
            	break;
            case 5: // Z
            	aircraft_values.coordz = stof(data);
            	break;
            case 6: // Speed X
            	aircraft_values.speedx = stof(data);
            	break;
            case 7: // Speed Y
            	aircraft_values.speedy = stof(data);
            	break;
            case 8: // Speed Z
            	aircraft_values.speedz = stof(data);

            	Aircraft new_aircraft(aircraft_values.ID, aircraft_values.entrancetime,
            			aircraft_values.coordx, aircraft_values.coordy, aircraft_values.coordz,
						aircraft_values.speedx,aircraft_values.speedy, aircraft_values.speedz);

            	aircraftList.push_back(&new_aircraft);
            	reset = 1; // Resets next block of data to make aircraft object
            	break;
            }
            reset++;
            index = 0; // Reset index for next line
        }
        else {
            ++index; // Increment index
        }
    }

	/* Close the file */
	close( input_file );
}

void System::simulate() {
	int period_sec = 1;
	cTimer timer(period_sec, 0); //initialize, set, and start the timer

	int time = 0;
	int count = 0;

	while (true) {
		time = count * period_sec;

		if ((time % 1) == 0) {
			if ((time % 5) == 0) {
				radar->display();
			}
			for (size_t i = 0; i < aircraftList.size(); ++i) {
				if (aircraftList[i]->isActive()) {
					for (size_t j = i + 1; j < aircraftList.size(); ++j) {
						if (aircraftList[j]->isActive()) {
							if (((fabs(aircraftList[i]->getX()- aircraftList[j]->getX()) <= 3000) &&
								(fabs(aircraftList[i]->getY()- aircraftList[j]->getY())<= 3000)) &&
								(fabs(aircraftList[i]->getZ()- aircraftList[j]->getZ())<= 1000))
							{
								std::cout << "WARNING: Aircraft"
										<< aircraftList[i]->getId()
										<< " and Aircraft"
										<< aircraftList[j]->getId()
										<< " TOO CLOSE.\n";
							}
						}
					}
				}
			}
			if ((time % 6 == 0)) {
				opCon->operator_console_request();
			}
		}
		count++;
		timer.waitTimer();
	} //end_while
}
;
