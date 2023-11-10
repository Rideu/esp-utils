// C helper library 

#ifndef LOCK_H
#define LOCK_H

#include <stdio.h>
#include <stdlib.h> 
#include "freertos/semphr.h"

#define INFINITE portMAX_DELAY 
#define DWORD unsigned long

typedef struct {
	QueueHandle_t smrHandle;
	unsigned char set;
} lock_event;


lock_event* lock_Create(void)
{
	lock_event* ev = (lock_event*)malloc(sizeof(lock_event));

	ev->set = 0;
	ev->smrHandle = xSemaphoreCreateCounting(1, 0);

	return ev;
}

/* Sets the state of the event to signaled, allowing one or more waiting threads to proceed.  */
void lock_Set(lock_event* lock) {
	lock->set = 1;
	xSemaphoreGive(lock->smrHandle);
}

/* Sets the state of the event to nonsignaled, causing threads to block. */
void lock_Reset(lock_event* lock) {

	lock->set = 0;
}

/*Blocks the current thread until the current lock_event* lock receives a signal*/
DWORD lock_Wait(lock_event* lock) {

	if (lock->set == 0)
	{

		DWORD wr = xSemaphoreTake(lock->smrHandle, INFINITE);
		return wr;
	}
	return 0;
}
#endif 