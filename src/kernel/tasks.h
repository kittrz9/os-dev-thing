#ifndef TASK_H
#define TASK_H

#include <stdint.h>

// arbitrary
#define MAX_TASKS 32

extern uint8_t tasksBlocked;

typedef enum {
	TASK_RUNNING,
	TASK_SLEEPING,
	TASK_WAITING, // will probably use this for the shell if I get around to making it a standalone task
} taskState;

typedef struct {
	uint8_t present; // ideally should implement some sort of sorting and mark the end of the list some way
	void* stack; // 1 page should be fine?

	taskState state;

	uint32_t timer;
	uint32_t timerRefresh;

	uint32_t sleepTimer;

	// cpu state
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;

	uint32_t esp;
	uint32_t ebp;

	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
} task;

// function shouldn't return, should call some end task syscall
void addTask(void (*func)(), uint32_t time);
void removeTask(void (*func)());

void processTasks(void);

void sleep(uint32_t ms);

#endif
