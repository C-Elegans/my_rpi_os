//
//  graphics.c
//  my_rpi_os
//
//  Created by Michael Nolan on 2/6/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#include "graphics.h"
#include "video.h"
#include "stdlib.h"

void set_pixel(short* framebuffer, int x, int y, short color){
	framebuffer+= y*SCREEN_WIDTH + x;
	*framebuffer = color;
}
void line(void* framebuffer, vec2 a, vec2 b, short color){
	int x0 = a.x * SCREEN_WIDTH;
	int x1 = b.x * SCREEN_WIDTH;
	int y0 = a.y * SCREEN_HEIGHT;
	int y1 = b.y * SCREEN_HEIGHT;
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		set_pixel(framebuffer,x0,y0,color);
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
	
}
int inside(int x,int y,int x0,int y0, int x1, int y1, int x2, int y2){
	
}
void triangle(short* framebuffer,vec2 a, vec2 b, vec2 c, short color){

	line(framebuffer,a,b,color);
	line(framebuffer,b,c,color);
	line(framebuffer,c,a,color);
}
/*void line(int x0, int y0, int x1, int y1) {
 
 int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
 int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
 int err = (dx>dy ? dx : -dy)/2, e2;
 
 for(;;){
 setPixel(x0,y0);
 if (x0==x1 && y0==y1) break;
 e2 = err;
 if (e2 >-dx) { err -= dy; x0 += sx; }
 if (e2 < dy) { err += dx; y0 += sy; }
 }
 }*/