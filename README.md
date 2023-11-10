  
---
# esp-utils

ESP32[^1]/8266[^2] utils library.

### task.h[^3]
Asynchronous task creation management.

Basic usage:

```c

void add(void* st)
{
	task* t = (task*)(st);

	int* b = (int*)t->args;

	int sum = 1 + *b;

	printf("%i", sum); 
}

int main(void)
{
	int b = 1;
	task_Run(&add, &b);
}
```

### lock.h[^4]

A reset event management used for thread synchronization.

Basic usage:

```c

lock_event* lock;

void lockTask(void* st)
{
	int switch = 0;

	while(1)
	{
		lock_Wait(lock); // wait for the signal

		printf((switch ^= 1)? "beep" : "boop"); // runs once signalled
	}
}

int main(void)
{ 
	lock = lock_Create();

	task_Run(&lockTask, NULL);

	while(1)
	{
		task_Sleep(1000);
		
		lock_Set(lock); // Set the state to signaled
	}
}
```

[^1]:https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/
[^2]:https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/api-reference/index.html
[^3]:https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html?highlight=xtaskcreate#tasks
[^4]:https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html?highlight=xsemaphoretake#semaphore-api


