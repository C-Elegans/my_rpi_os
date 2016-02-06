//
//  graphics.h
//  my_rpi_os
//
//  Created by Michael Nolan on 2/6/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#ifndef graphics_h
#define graphics_h
typedef struct{
	float x;
	float y;
	float z;
}vec3;
typedef struct{
	float x;
	float y;
}vec2;
void set_pixel(short* framebuffer, int x, int y, short color);
void line(void* framebuffer, vec2 a,vec2 b, short color);
void triangle(short* framebuffer,vec2 a, vec2 b, vec2 c, short color);
#endif /* graphics_h */
