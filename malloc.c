//
//  malloc.c
//  my_rpi_os
//
//  Created by Michael Nolan on 1/29/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#include "malloc.h"
#define BRK_MAX    0x40000
void* __brk__ = 0x20000;

void* sbrk(size_t increment){
	void* old_brk = __brk__;
	if(((size_t)__brk__ + increment) > BRK_MAX){
		return NULL;
	}
	__brk__ += increment;
	return old_brk;
}






