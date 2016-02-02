//
//  stdlib.h
//  my_rpi_os
//
//  Created by Michael Nolan on 2/1/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#ifndef stdlib_h
#define stdlib_h
#include "malloc.h"

typedef struct {
	int	quot;
	int	rem;
} div_t;

div_t div(int numerator, int denominator);

typedef struct {
	long int	quot;
	long int	rem;
} ldiv_t;

ldiv_t ldiv(long numerator, long denominator);

int abs(int __x);
long labs(long __x);


long strtol(const char *, char **, int);
unsigned long strtoul(const char *, char **, int);

int atoi(const char *p);
long atol(const char *p);
char *itoa(int num, char *str, int radix);
char *utoa(unsigned num, char *str, int radix);
char *ltoa(long num, char *str, int radix);
char *ultoa(unsigned long num, char *str, int radix);


void *bsearch(const void *, const void *, size_t, size_t, register int (*compar)(const void *, const void *));



#ifndef RAND_MAX
#define RAND_MAX        0x7fffffffL
#endif

int rand(void);
void srand(unsigned __seed);
int rand_r(unsigned *__seed);


#endif /* stdlib_h */
