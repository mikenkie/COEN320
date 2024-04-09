/*
 * OperatorConsole.h
 *
 *  
 * Author: mikenkie
 */
#ifndef OPERATORCONSOLE_H_
#define OPERATORCONSOLE_H_


#include "Aircraft.h"
#include <sys/dispatch.h>
#include <pthread.h>


typedef struct _my_data {
	std::string command;
	float data;
} my_data_t;


class OperatorConsole {
    private:
        Aircraft* aircraft;
        pthread_mutex_t mutex;

    public:
        // Constructor
        OperatorConsole();
        OperatorConsole(Aircraft* ar);

        // Method to allow controller to change which aircraft they wish to control
        void requestAircraftControlChange (Aircraft* ar);
        Aircraft* getAircraftConsole () const;

        void operator_console_request();
        void sporadic_task();

};

#endif
