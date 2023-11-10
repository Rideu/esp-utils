// C helper library 

#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdlib.h>   

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h" 

//static const char* task_TAG = "scan";

typedef struct {
	int taskID;
	TaskHandle_t* taskHandle;

	void* func;
	void* args;
	void* result;
} task;

void task_proc(void* taskData)
{

	task* t = ((task*)taskData);

	void* (*func)(task*) = (void*(*)(task*))(t->func);

	void* result = (*func)(t);

	t->result = result; // TODO
	//task* t = ((task*)taskargs);

	//void* (*func)() = (t->func);

	///*void* result = */(*func)(t->args);

	free(t);
	vTaskDelete(NULL);
}

static const char* defaultTaskName = "NAME";
static int taskPoolIDs;

task* task_Run(void* func, void* args)
{
	taskPoolIDs++;
	TaskHandle_t h = NULL;

	task* t = (task*)malloc(sizeof(task));

	t->taskID = taskPoolIDs;
	t->func = func;
	t->args = args;
	t->taskHandle = &h;

	xTaskCreate(task_proc, defaultTaskName, 1024 * 3, t, tskIDLE_PRIORITY, &h);

	return t;
}

void task_Sleep(int ms)
{ 
	vTaskDelay(ms / portTICK_PERIOD_MS);
}
/* Waits until the task t is evaluated */
//void task_Wait(task* t)
//{
//	//WaitForSingleObject(t->taskHandle, INFINITE);
//}
#endif  