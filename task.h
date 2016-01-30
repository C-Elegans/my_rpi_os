//
//  task.h
//  my_rpi_os
//
//  Created by Michael Nolan on 1/29/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#ifndef task_h
#define task_h
void add_task(void(*task)(void));
void yield();
void exit();
void task_init();
#endif /* task_h */
