//
//  malloc.h
//  my_rpi_os
//
//  Created by Michael Nolan on 1/29/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//
#include "types.h"
extern void* brk;
void* sbrk(size_t);
void* malloc(size_t);
void* calloc(size_t,size_t);
void* realloc(void*,size_t);