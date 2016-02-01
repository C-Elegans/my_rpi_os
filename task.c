//
//  task.c
//  my_rpi_os
//
//  Created by Michael Nolan on 1/29/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#include "task.h"
#include "malloc.h"
struct pcb {
	int		sr, ilr, r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr;
	struct pcb *	next;
} pcb;

/*struct malloc_info {
 *      size_t size;
 *      struct malloc_info *next;
 *      int free;
 * #ifdef DEBUG
 *      int magic;
 * #endif
 * };*/
struct pcb *list_handle = NULL;
void add_task(void (*func)(void)){
	struct pcb *newtask = malloc(sizeof(struct pcb));

	newtask->ilr = (int)func;
	newtask->sp = (int)malloc(1024) + 1024;
	struct pcb *oldtask = list_handle;
	list_handle = newtask;
	newtask->next = oldtask;
	struct pcb *task = oldtask;
	while (task->next != oldtask)
		task = task->next;
	task->next = newtask;
}
void exit();
void task_init(){
	struct pcb *newtask = malloc(sizeof(struct pcb));

	list_handle = newtask;
	newtask->next = newtask;
}
