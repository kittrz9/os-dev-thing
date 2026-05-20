#include "tasks.h"

#include "serial.h"
#include "pageAlloc.h"

task currentTasks[MAX_TASKS];

void addTask(void (*func)(), uint32_t time) {
	task* t = NULL;
	for(uint32_t i = 0; i < MAX_TASKS; ++i) {
		if(currentTasks[i].present == 0) {
			t = &currentTasks[i];
			break;
		}
	}
	if(t == NULL) {
		serialWriteStr("too many tasks!!!!!!\n");
		__asm__ volatile ("cli; hlt");
	}

	t->present = 1;

	t->timer = time;
	t->timerRefresh = time;

	t->stack = pageAlloc(4096); // no stack protection lmao

	t->eax = 0;
	t->ebx = 0;
	t->ecx = 0;
	t->edx = 0;
	t->esi = 0;
	t->edi = 0;

	t->sleepTimer = 0;

	t->esp = (uint32_t)t->stack;
	t->ebp = t->esp; // ?

	t->eip = (uint32_t)func;

	// copied from https://wiki.osdev.org/Cooperative_Multitasking
	// because I fucking hate this stupid asm syntax
	__asm__ volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(t->eflags)::"%eax");
	serialWriteStr("task added, eip at: ");
	serialWriteHex32(t->eip);
	serialWriteStr("\n");
}
//void removeTask(void (*func)());

extern uint32_t currentTaskRegisters[];
static uint32_t currentTaskIndex = MAX_TASKS;
void processTasks() {
	for(uint32_t i = 0; i < MAX_TASKS; ++i) {
		if(currentTasks[i].sleepTimer > 0) {
			--currentTasks[i].sleepTimer;
		}
	}

	task* t = &currentTasks[currentTaskIndex];
	if(currentTaskIndex == MAX_TASKS) {
		t = &currentTasks[0];
		if(t->present == 0) {
			return; // it should pull all the register values back from the array that are still there
		}
		currentTaskIndex = 0;
		currentTaskRegisters[0] = t->eax;
		currentTaskRegisters[1] = t->ebx;
		currentTaskRegisters[2] = t->ecx;
		currentTaskRegisters[3] = t->edx;
		currentTaskRegisters[4] = t->esi;
		currentTaskRegisters[5] = t->edi;
		currentTaskRegisters[6] = t->esp;
		currentTaskRegisters[7] = t->ebp;
		currentTaskRegisters[8] = t->eip;
		currentTaskRegisters[9] = t->cs;
		currentTaskRegisters[10] = t->eflags;
		return;
	}

	--t->timer;
	if(t->timer != 0) {
		return;
	}
	// it should end up with the old task index if there's no other tasks
	uint32_t oldTaskIndex = currentTaskIndex;
	++currentTaskIndex;
	currentTaskIndex %= MAX_TASKS;
	while(currentTaskIndex != oldTaskIndex) {
		// ideally there should always be at least one task that isn't sleeping (the kernel), so this shouldn't end up switching to a task that should be sleeping
		// though there really should be some place that it jumps to to wait out if there's absolutely no tasks to switch to
		if(currentTasks[currentTaskIndex].present == 1 && currentTasks[currentTaskIndex].sleepTimer == 0) {
			break;
		}
		++currentTaskIndex;
		currentTaskIndex %= MAX_TASKS;
	}
	t->timer = t->timerRefresh;

	/*serialWriteStr("TASK SWITCH!!!\n");
	serialWriteStr("task id: ");
	serialWriteHex32(currentTaskIndex);
	serialWriteStr("\n");*/
	t->eax = currentTaskRegisters[0];
	t->ebx = currentTaskRegisters[1];
	t->ecx = currentTaskRegisters[2];
	t->edx = currentTaskRegisters[3];
	t->esi = currentTaskRegisters[4];
	t->edi = currentTaskRegisters[5];
	t->esp = currentTaskRegisters[6];
	t->ebp = currentTaskRegisters[7];
	t->eip = currentTaskRegisters[8];
	t->cs = currentTaskRegisters[9];
	t->eflags = currentTaskRegisters[10];
	t = &currentTasks[currentTaskIndex];
	currentTaskRegisters[0] = t->eax;
	currentTaskRegisters[1] = t->ebx;
	currentTaskRegisters[2] = t->ecx;
	currentTaskRegisters[3] = t->edx;
	currentTaskRegisters[4] = t->esi;
	currentTaskRegisters[5] = t->edi;
	currentTaskRegisters[6] = t->esp;
	currentTaskRegisters[7] = t->ebp;
	currentTaskRegisters[8] = t->eip;
	currentTaskRegisters[9] = t->cs;
	currentTaskRegisters[10] = t->eflags;
	/*serialWriteStr("EAX: ");
	serialWriteHex32(currentTaskRegisters[0]);
	serialWriteStr("\n");
	serialWriteStr("EBX: ");
	serialWriteHex32(currentTaskRegisters[1]);
	serialWriteStr("\n");
	serialWriteStr("ECX: ");
	serialWriteHex32(currentTaskRegisters[2]);
	serialWriteStr("\n");
	serialWriteStr("EDX: ");
	serialWriteHex32(currentTaskRegisters[3]);
	serialWriteStr("\n");
	serialWriteStr("ESI: ");
	serialWriteHex32(currentTaskRegisters[4]);
	serialWriteStr("\n");
	serialWriteStr("EDI: ");
	serialWriteHex32(currentTaskRegisters[5]);
	serialWriteStr("\n");
	serialWriteStr("ESP: ");
	serialWriteHex32(currentTaskRegisters[6]);
	serialWriteStr("\n");
	serialWriteStr("EBP: ");
	serialWriteHex32(currentTaskRegisters[7]);
	serialWriteStr("\n");
	serialWriteStr("EIP: ");
	serialWriteHex32(currentTaskRegisters[8]);
	serialWriteStr("\n");
	serialWriteStr("CS: ");
	serialWriteHex32(currentTaskRegisters[9]);
	serialWriteStr("\n");
	serialWriteStr("EFLAGS: ");
	serialWriteHex32(currentTaskRegisters[10]);
	serialWriteStr("\n");*/
}

void sleep(uint32_t ms) {
	serialWriteHex32(currentTaskIndex);
	serialWriteStr("\n");
	currentTasks[currentTaskIndex].sleepTimer = ms;
	// force a task switch
	currentTasks[currentTaskIndex].timer = 1;
	//__asm__ volatile("int $32");
	// this still lets the current task run for a bit until the timer interrupt happens again
	// it should switch immediately and probably reset the timer but I can't get it to do that by just forcing the interrupt with the instruction
	// I could probably make it do it manually but I don't care enough right now
}
