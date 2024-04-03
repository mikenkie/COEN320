#include <iostream>
using namespace std;

#include "Aircraft.h"
#include <vector>
#include <pthread.h>

// Thread function
void* aircraftThread(void* arg) {
    Aircraft* aircraft = static_cast<Aircraft*>(arg);
    aircraft->simulate();
    return NULL;
}

int main() {
    // Create two aircraft
    Aircraft aircraft1(0, 0, 0, 0, 10, 20, 0 ), aircraft2(1, 0, 0, 0, -10, -20, 0 );

    // Create two threads
    pthread_t thread1, thread2;

    // Start the threads, passing each thread its corresponding aircraft
    pthread_create(&thread1, NULL, aircraftThread, &aircraft1);
    pthread_create(&thread2, NULL, aircraftThread, &aircraft2);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

