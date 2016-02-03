//
//  list.h
//  my_rpi_os
//
//  Created by Michael Nolan on 2/3/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#ifndef list_h
#define list_h
#include "types.h"
struct list{
	struct list* next;
	struct list* previous;
	size_t payload_size;
	void* payload;
};
struct list* create_list(int payload_size, void* payload);
void add_element(struct list*, int, void* payload);
void remove_element(struct list*);
#endif /* list_h */
