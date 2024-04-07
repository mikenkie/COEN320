using namespace std;

#include "Aircraft.h"
#include "Radar.h"
#include "OperatorConsole.h"
#include "CommunicationSystem.h"
#include "DataDisplay.h"

#include <vector>
#include <iostream>
#include <pthread.h>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "cTimer.h"
#include <sys/dispatch.h>
#include <sys/siginfo.h>
#include <sys/trace.h>


struct ThreadArgs {
    CommunicationSystem* communicationSystem;
    DataDisplay* dataDisplay;
    Aircraft* aircraft;
};
/* Message passing between ATC and Operator Console.
 * Establishes a channel between the ATC and OC. The OC establishes the channel to initiate connection. ATC
 * attaches to the channel to establish connection.
 */

void* ats_start_messaging(void* argsPtr) {
	ThreadArgs* args = static_cast<ThreadArgs*>(argsPtr);

	CommunicationSystem* cs = args->communicationSystem;
	DataDisplay* dp = args->dataDisplay;
	Aircraft* ar = args->aircraft;

	name_attach_t *attach;
	my_data_t msg;

	int rcvid;
	/* Create a local name (/dev/name/local/...) */
		if ((attach = name_attach(NULL, ATTACH_POINT, 0)) == NULL) {
			perror("Error occurred while creating the channel");
		}

		/* Do your MsgReceive's here now with the chid */
		while (true) {
			rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);

			if (rcvid == -1) {/* Error condition, exit */
				break;
			}

			if (rcvid == 0) {/* Pulse received */
				switch (msg.pulse.code) {
				case _PULSE_CODE_DISCONNECT:
					ConnectDetach(msg.pulse.scoid);
					break;
				case _PULSE_CODE_UNBLOCK:
					//Message Reply later in the code
					break;
				default:
					break;
				}
				continue;
			}

			/* name_open() sends a connect message, must EOK this */
			if (msg.pulse.type == _IO_CONNECT ) {
				MsgReply( rcvid, EOK, NULL, 0 );
				continue;
			}

			/* Some other QNX IO message was received; reject it */
			if (msg.pulse.type > _IO_BASE && msg.pulse.type <= _IO_MAX ) {
				MsgError( rcvid, ENOSYS );
				continue;
			}

			if (msg.pulse.type == 0x00) {
				/*A motion message has been received*/
				if (msg.pulse.subtype == 0x01) {
					/* A velocity message has been received  */
					printf("ATC receiving the the message..");

					if (msg.command.compare("POSX") == 0) {
						cs->executeChangePositionX (*ar, msg.data);
					}
					else if (msg.command.compare("POSY") == 0) {
						cs->executeChangePositionY (*ar, msg.data);
					}
					else if (msg.command.compare("POSZ") == 0) {
						cs->executeChangePositionZ (*ar, msg.data);
					}
					else if (msg.command.compare("SPEEDX") == 0) {
						cs->executeChangeSpeedX(*ar, msg.data);
					}
					else if (msg.command.compare("SPEEDY") == 0) {
						cs->executeChangeSpeedY(*ar, msg.data);
					}
					else if (msg.command.compare("SPEEDZ") == 0) {
						cs->executeChangeSpeedZ(*ar, msg.data);
					}
					else if (msg.command.compare("SEND INFO TO RADAR") == 0) {
						dp->displayInfoToRadar(*ar);
					}
				}
				else{
					MsgError(rcvid, ENOSYS );
					continue;
				}
			}

			MsgReply(rcvid, EOK, 0, 0);

		}// while loop

		/* Remove the name from the space */
		name_detach(attach, 0);
		return EXIT_SUCCESS;

}//function


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
    operatorConsole->operator_console_start_messaging ();
    return NULL;
}


int main() {
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

    // Testing ATC and OC communication
    pthread_t th1, th2;

    OperatorConsole oc;
    CommunicationSystem commSys;
    DataDisplay dp;

    ThreadArgs args;
    args.communicationSystem = &commSys;
    args.dataDisplay = &dp;
    args.aircraft = &aircraft1;


    pthread_create(&th1, NULL, operatorConsoleThread, &oc);
    pthread_create(&th2, NULL, &ats_start_messaging,&args);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0;
}



