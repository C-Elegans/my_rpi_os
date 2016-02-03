//
//  list.c
//  my_rpi_os
//
//  Created by Michael Nolan on 2/3/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#include "list.h"
#include "malloc.h"
struct list* create_list(int payload_size, void* payload){
	struct list* newlist = (struct list*)malloc(sizeof(struct list));
	newlist->next = NULL;
	newlist->previous = NULL;
	newlist->payload_size = payload_size;
	newlist->payload = payload;
	return newlist;
}
void add_element(struct list* list, int payload_size, void* payload){
	struct list* newelement = (struct list*)malloc(sizeof(struct list));
	newelement->next = list->next;
	list->next = newelement;
	newelement->previous = list;
	newelement->payload_size = payload_size;
	newelement->payload = payload;
}
void remove_element(struct list* list){
	list->previous->next = list->next;
	list->next->previous = list->previous;
	free(list);
}
