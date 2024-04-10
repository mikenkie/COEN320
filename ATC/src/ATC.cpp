using namespace std;

#include "Aircraft.h"
#include "Radar.h"
#include "OperatorConsole.h"
#include "CommunicationSystem.h"
#include "DataDisplay.h"
#include "System.h"

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


void *aircraftThread(void* arg) {
    Aircraft* aircraft = static_cast<Aircraft*>(arg);
    aircraft->simulate();
    return NULL;
}
void *radarThread(void* arg) {
    Radar* radar = static_cast<Radar*>(arg);
    radar->simulate();
    return NULL;
}
void *systemThread(void* arg) {
    System* system = static_cast<System*>(arg);
    system->simulate();
    return NULL;
}

void *operatorConsoleThread(void* arg) {
    OperatorConsole* operatorConsole = static_cast<OperatorConsole*>(arg);
    operatorConsole->operator_console_request();
    return NULL;
}

void *writeToFile(void* arg) {
	vector <Aircraft*>* myList = static_cast<vector <Aircraft*>*>(arg);

	// Create shared output file
	int  fd;
	int  size_written;

	// To find the file navigate in the vmware
	fd = creat( "/data/home/myOutputFile.txt", S_IRUSR | S_IWUSR | S_IXUSR );
	
	if (fd != -1) {
		int period_sec = 1;
		cTimer timer(period_sec, 0); //initialize, set, and start the timer

		int time = 0;
		int count = 0;

		while (true) {
			time = count * period_sec;

			if ((time % 20) == 0) {
				for (Aircraft *currentAircraft: *myList) {
					std::string info = "Aircraft ID: " + std::to_string(currentAircraft->getId()) +
						               "\nAltitude: " + std::to_string(currentAircraft->getZ()) +
						               "\nLongitude: " + std::to_string(currentAircraft->getX()) +
						               "\nLatitude: " + std::to_string(currentAircraft->getY()) +
						               "\nSpeed: " + std::to_string(currentAircraft->getSpeedX());

					//int length = info.length();
					//char buffer[]= new char [length + 1];
					//strcpy (buffer,info.c_str());
					//char buffer [] = {info.c_str()};

					char buffer[info.length() + 1];
					strcpy(buffer, info.c_str());

					size_written = write( fd, buffer, sizeof( buffer ) );
					if( size_written != sizeof( buffer ) )
						perror( "Error writing myfile.dat" );
				}
			}
			count++;
			timer.waitTimer();
		}

		close(fd);
	}

	return NULL;
}


int main() {

    // Create two aircraft
    Aircraft aircraft1(0, 0, 0, 0, 0, 1000, 2000, 0 ), aircraft2(1, 0, 100000, 100000, 0, -1000, -2000, 0 ), aircraft3(2, 0, 100000, 100000, 0, -1000, -2000, 0 );
    vector<Aircraft*> acVec;

    acVec.push_back(&aircraft1);
//    acVec.push_back(&aircraft2);
//    acVec.push_back(&aircraft3);

    //initialize radar
    Radar radar(acVec);
    OperatorConsole oc(acVec);
    System system(acVec, &radar, &oc);
    // Create two threads
    pthread_t thread1, thread2, thread3, rThread, sThread, ocThread, writeThread;

    // Start the threads, passing each thread its corresponding aircraft
    pthread_create(&thread1, NULL, aircraftThread, &aircraft1);
//    pthread_create(&thread2, NULL, aircraftThread, &aircraft2);
//    pthread_create(&thread3, NULL, aircraftThread, &aircraft3);
    pthread_create(&writeThread, NULL, writeToFile, &acVec);
    pthread_create(&rThread, NULL, radarThread, &radar);
    pthread_create(&sThread, NULL, systemThread, &system);
    pthread_create(&ocThread, NULL, operatorConsoleThread, &oc);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
//    pthread_join(thread2, NULL);
//    pthread_join(thread3, NULL);
    pthread_join(rThread, NULL);
    pthread_join(ocThread, NULL);
    pthread_join(writeThread, NULL);
    return 0;
}



