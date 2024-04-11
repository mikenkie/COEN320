using namespace std;

#include "Aircraft.h"
#include "Radar.h"
#include "OperatorConsole.h"
#include "CommunicationSystem.h"
#include "DataDisplay.h"
#include "System.h"
#include "fileWriter.h"

#include <vector>
#include <iostream>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "cTimer.h"
#include <sys/dispatch.h>
#include <sys/siginfo.h>
#include <sys/trace.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>

void* aircraftThread(void *arg) {
	Aircraft *aircraft = static_cast<Aircraft*>(arg);
	aircraft->simulate();
	return NULL;
}
void* radarThread(void *arg) {
	Radar *radar = static_cast<Radar*>(arg);
	radar->simulate();
	return NULL;
}
void* systemThread(void *arg) {
	System *system = static_cast<System*>(arg);
	system->simulate();
	return NULL;
}

void* operatorConsoleThread(void *arg) {
	OperatorConsole *operatorConsole = static_cast<OperatorConsole*>(arg);
//	operatorConsole->operator_console_request();
	return NULL;
}

void* write_to_file(void *arg) {
	vector<Aircraft*> *myList = static_cast<vector<Aircraft*>*>(arg);

	// Create shared output file
	int fd;
	int size_written;

	// To find the file navigate in the vmware
	fd = creat("/data/home/myOutputFile.txt", S_IRUSR | S_IWUSR | S_IXUSR);

	if (fd != -1) {
		int period_sec = 1;
		cTimer timer(period_sec, 0); //initialize, set, and start the timer

		int time = 0;
		int count = 0;

		while (true) {
			time = count * period_sec;

			if ((time % 6) == 0) {
				for (Aircraft *currentAircraft : *myList) {
					std::string info = "Aircraft ID: "
							+ std::to_string(currentAircraft->getId())
							+ "\nAltitude: "
							+ std::to_string(currentAircraft->getZ())
							+ "\nLongitude: "
							+ std::to_string(currentAircraft->getX())
							+ "\nLatitude: "
							+ std::to_string(currentAircraft->getY())
							+ "\nSpeed: "
							+ std::to_string(currentAircraft->getSpeedX())
							+ "\n";

					char buffer[info.length() + 1];
					strcpy(buffer, info.c_str());

					size_written = write(fd, buffer, sizeof(buffer));
					if (size_written != sizeof(buffer))
						perror("Error writing myfile.dat");
				}
			}
			count++;
			timer.waitTimer();
		}

		close(fd);
	}

	return NULL;
}

// This is used to generate data of aircrafts from input file
typedef struct _my_aircraft {
	int entrancetime;
	int ID;
	float coordx, coordy, coordz;
	float speedx, speedy, speedz;
} my_aircraft_t;

vector<Aircraft*> read_aircrafts_from_input_file(char* filep) {
/*	char *cwd;
	char buff[PATH_MAX];
	cwd = getcwd(buff, PATH_MAX);
	if (cwd != NULL) {
		printf("My working directory is %s.\n", cwd);
	}*/
	vector<Aircraft*> my_aircraft_list;
	my_aircraft_t aircraft_values;
	int input_file;
	int size_read;
	char buffer[3123];
	int index = 0;

	int reset = 1; // The number of lines in text file that defines an aircraft

	/*
	 * Open a file for input but replace file you want to read with the path.
	 * For testing, we have four files: input_low, input_medium, input_high, input_overload.
	 */
	input_file = open(filep, O_RDONLY);

	// Read characters from file until end of file is encountered
	while ((size_read = read(input_file, &buffer[index], 1)) > 0) {
		// If the reader reaches the end of the line, else continues to add character to buffer
		if (buffer[index] == '\n' || index == sizeof(buffer) - 1) {
			// Print content read up to newline character or end of buffer
			buffer[index] = '\0'; // Null-terminate the string
			std::cout << "Line: " << buffer << std::endl; //Debug message

			/* Test for error */
			if (size_read == -1)
				perror("Error reading input file.");

			// Extract values
			std::string data;

			int i = 0;
			// We do not want the information that comes before the data. Ex. Time 5. We do not want "Time"
			for (i = 0; buffer[i] != '\0'; ++i) {
				if (buffer[i] == ' ') {
					break;
				}
			}

			// Extra data as a string
			for (int j = i + 1; buffer[j] != '\0'; ++j) {
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

				Aircraft *new_aircraft = new Aircraft(aircraft_values.ID,
						aircraft_values.entrancetime, aircraft_values.coordx,
						aircraft_values.coordy, aircraft_values.coordz,
						aircraft_values.speedx, aircraft_values.speedy,
						aircraft_values.speedz);

				my_aircraft_list.push_back(new_aircraft);
				reset = 0; // Resets next block of data to make aircraft object
				break;
			}

			reset++;
			index = 0; // Reset index for next line
		} else {
			++index; // Increment index
		}
	}

	/* Close the file */
	close(input_file);

	return my_aircraft_list;
}

char* choose_input_file() {
	char* path;
	string x;
	int option;

	cout << "Type in the integer operating condition: \n"
	     << "1. Low\n"
		 << "2. Medium\n"
		 << "3. High\n"
		 << "4. Overload\n" << endl;

	cin >> option;

	switch(option) {
	case 1:
		x = "input_low.txt";
		path = new char[x.length() + 1];
		copy(x.begin(), x.end(), path);
		break;
	case 2:
		x = "input_medium.txt";
		path = new char[x.length() + 1];
		copy(x.begin(), x.end(), path);
		break;
	case 3:
		x = "input_high.txt";
		path = new char[x.length() + 1];
		path = copy(x.begin(), x.end(), path);
		break;
	case 4:
		x = "input_overload.txt";
		path = new char[x.length() + 1];
		copy(x.begin(), x.end(), path);
		break;
	}

	return path;
}

int main() {
//	fileWriter writer = fileWriter();
//	writer.writeLow();
//	writer.writeMed();
//	writer.writeHigh();
//	writer.writeOver();

	char* file_path = choose_input_file();
	// Create two aircraft
	//Aircraft aircraft1(0, 0, 0, 0, 20000, 1000, 2000,  0), aircraft2(1, 0, 100000, 100000, 20000, -1000, -2000, 0 ), aircraft3(2, 10, 100000, 100000, 20000, -1000, -2000, 0 );
	vector<Aircraft*> acVec = read_aircrafts_from_input_file(file_path);

	//acVec.push_back(&aircraft1);
	//acVec.push_back(&aircraft2);
	// acVec.push_back(&aircraft3);

	Radar radar(acVec);
	OperatorConsole oc(acVec);
	System system(acVec, &radar, &oc);

	vector<pthread_t> acThreads;

	for (Aircraft* ac : acVec) {
		pthread_t acthread;
		acThreads.push_back(acthread);
	}
	// Create two threads
	pthread_t rThread, sThread, ocThread, writeThread;
	for (size_t i = 0; i < acVec.size(); i++) {
		pthread_create(&acThreads[i], NULL, aircraftThread, acVec[i]);
	}

	// Start the threads, passing each thread its corresponding aircraft
//	pthread_create(&thread1, NULL, aircraftThread, acVec.at(0));
//	pthread_create(&thread2, NULL, aircraftThread, &acVec.at(1));
//	pthread_create(&thread3, NULL, aircraftThread, &acVec.at(2));
	pthread_create(&writeThread, NULL, write_to_file, &acVec);
	pthread_create(&rThread, NULL, radarThread, &radar);
	pthread_create(&sThread, NULL, systemThread, &system);
	pthread_create(&ocThread, NULL, operatorConsoleThread, &oc);

	// Wait for the threads to finish
//	pthread_join(thread1, NULL);
//    pthread_join(thread2, NULL);
//    pthread_join(thread3, NULL);
	pthread_join(rThread, NULL);
	pthread_join(ocThread, NULL);
	pthread_join(writeThread, NULL);
	return 0;
}

