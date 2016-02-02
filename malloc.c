//
//  malloc.c
//  my_rpi_os
//
//  Created by Michael Nolan on 1/29/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#include "malloc.h"
#include "string.h"

#define DEBUG
void *brk = (void *)0x20000;

void *global_base = NULL;
struct malloc_info {
	size_t			size;
	struct malloc_info *	next;
	int			free;
#ifdef DEBUG
	int			magic;
#endif
};
#define BLOCK_SIZE sizeof(struct malloc_info)
void *sbrk(size_t increment){
	void *old_brk = brk;

	brk += increment;
	brk = (void *)(((int)brk + 3) & ~0x3);
	return old_brk;
}





struct malloc_info *find_free_block(struct malloc_info **last, size_t size){
	struct malloc_info *current = global_base;

	while (current && !(current->free && current->size >= size)) {
		*last = current;
		current = current->next;
	}
	return current;
}
struct malloc_info *get_block_ptr(void *ptr) {
	return (struct malloc_info *)ptr - 1;
}
struct malloc_info *request_space(struct malloc_info *last, size_t size){
	struct malloc_info *block;

	block = sbrk(0);
	void *request = sbrk(size + BLOCK_SIZE);
	if (request == (void *)-1) {
		//exit(-1);
	}
	if (last)
		last->next = block;
	block->size = size;
	block->next = NULL;
	block->free = 0;
	block->magic = 0xDEADBEEF;
	return block;
}
void *malloc(size_t size){
	struct malloc_info *block = find_free_block(global_base, size);

	if (size <= 0) return NULL;
	if (!global_base) {
		block = request_space(NULL, size);
		if (!block) return NULL;
		global_base = block;
	} else {
		struct malloc_info *last = global_base;
		block = find_free_block(&last, size);
		if (!block) {
			block = request_space(last, size);
			if (!block) return NULL;
		} else {
			block->free = 0;
			block->magic = 0x7777777;
		}
	}
	return block + 1;
}

void free(void *ptr){
	if (!ptr) return;
	struct malloc_info *block = ((struct malloc_info *)ptr) - 1;
	block->free = 1;
	block->magic = 0x55555555;
}
void *calloc(size_t nelm, size_t elsize){
	void *mem = malloc(nelm * elsize);

	memset(mem, 0, nelm * elsize);
	return mem;
}
void *realloc(void *ptr, size_t size){
	if (!ptr)
		return malloc(size);
	struct malloc_info *block = get_block_ptr(ptr);
	if (block->size >= size) //need to implement split
		return ptr;
	void *new_ptr = malloc(size);
	if (!new_ptr) return NULL;
	memcpy(new_ptr, ptr, block->size);
	free(ptr);
	return new_ptr;
}
