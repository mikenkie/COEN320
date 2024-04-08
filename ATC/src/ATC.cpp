using namespace std;

#include "Aircraft.h"
#include "Radar.h"
#include "OperatorConsole.h"
#include "CommunicationSystem.h"
#include "DataDisplay.h"

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

void *operatorConsoleThread(void* arg) {
    OperatorConsole* operatorConsole = static_cast<OperatorConsole*>(arg);
    operatorConsole->operator_console_request();
    return NULL;
}


int main() {
    // Create shared output file
	 int  fd;
	 int  size_written;
	 char buffer[] = { "A text record to be written" };

	 // To find the file navigate in the vmware
	 fd = creat( "/data/home/myOutputFile.txt", S_IRUSR | S_IWUSR | S_IXUSR );

	 size_written = write( fd, buffer, sizeof( buffer ) );

	 /* test for error              */
	 if( size_written != sizeof( buffer ) ) {
	    perror( "Error writing myfile.dat" );
	    return EXIT_FAILURE;
	}
    
    // Create two aircraft
    Aircraft aircraft1(0, 0, 0, 0, 0, 1000, 2000, 0 ), aircraft2(1, 0, 100000, 100000, 0, -1000, -2000, 0 ), aircraft3(2, 0, 100000, 100000, 0, -1000, -2000, 0 );
    vector<Aircraft*> acVec;

    acVec.push_back(&aircraft1);
    acVec.push_back(&aircraft2);
    acVec.push_back(&aircraft3);

    //initialize radar
    Radar radar(acVec);

    // Create two threads
    pthread_t thread1, thread2, thread3, rThread;

    // Start the threads, passing each thread its corresponding aircraft
    pthread_create(&thread1, NULL, aircraftThread, &aircraft1);
    pthread_create(&thread2, NULL, aircraftThread, &aircraft2);
    pthread_create(&thread3, NULL, aircraftThread, &aircraft3);
    pthread_create(&rThread, NULL, radarThread, &radar);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(rThread, NULL);

    // Testing Operating Console
    pthread_t ocThread;
    OperatorConsole oc(aircraft1);

    pthread_create(&ocThread, NULL, operatorConsoleThread, &oc);


    return 0;
}



