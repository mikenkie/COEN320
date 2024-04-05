#include <iostream>
using namespace std;

#include "Aircraft.h"
#include <pthread.h>
#include "Radar.h"
#include <vector>
#include <iostream>

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

int main() {
    // Create two aircraft
    Aircraft aircraft1(0, 0, 0, 0, 10, 20, 0 ), aircraft2(1, 0, 0, 0, -10, -20, 0 );
    vector<Aircraft*> acVec;

    acVec.push_back(&aircraft1);
    acVec.push_back(&aircraft2);

    //initialize radar
    Radar radar(acVec);

    // Create two threads
    pthread_t thread1, thread2, rThread;

    // Start the threads, passing each thread its corresponding aircraft
    pthread_create(&thread1, NULL, aircraftThread, &aircraft1);
    pthread_create(&thread2, NULL, aircraftThread, &aircraft2);
    pthread_create(&rThread, NULL, radarThread, &radar);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(rThread, NULL);

    return 0;
}
