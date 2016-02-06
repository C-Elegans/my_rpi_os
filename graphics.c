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
#include "math.h"
#include "uart.h"

void set_pixel(short* framebuffer, int x, int y, short color){
	framebuffer+= y*SCREEN_WIDTH + x;
	*framebuffer = color;
}
void set_pixelv(short* framebuffer, vec2 p, short color){
	int x = p.x * SCREEN_WIDTH;
	int y = p.y * SCREEN_HEIGHT;
	framebuffer+=y*SCREEN_WIDTH + x;
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
int same_side(vec2 p, vec2 a, vec2 b, vec2 c){
	float cp1 = cross2(sub(b,a),sub(p,a));
	float cp2 = cross2(sub(b,a),sub(c,a));
	if(cp1*cp2>=0)return 1;
	return 0;
}
/*function SameSide(p1,p2, a,b)
 cp1 = CrossProduct(b-a, p1-a)
 cp2 = CrossProduct(b-a, p2-a)
 if DotProduct(cp1, cp2) >= 0 then return true
 else return false*/
int inside(vec2 p, vec2 a, vec2 b, vec2 c){
	return same_side(p,a,b,c) && same_side(p,b,c,a) && same_side(p,c,a,b);
}
void triangle(short* framebuffer,vec2 a, vec2 b, vec2 c, short color){
	puts("entering triangle code\r\n");
	float dx = 1.0f/(float)SCREEN_WIDTH;
	float dy = .99f/(float)SCREEN_HEIGHT;
	vec2 p, max;
	puts("calculating min\r\n");
	p.x = fmin(a.x,b.x);
	p.x = fmin(p.x,c.x);
	p.y = fmin(a.y,b.y);
	p.y = fmin(p.y,c.y);
	puts("calculating max\r\n");
	max.x = fmax(a.x,b.x);
	max.x = fmax(p.x,c.x);
	max.y = fmax(a.y,b.y);
	max.y = fmax(p.y,c.y);
	float x_initial = p.x;
	for(;p.y<max.y;p.y=p.y+ dy){
		//puts("y: ");
		//uart_putint((int)(p.y*SCREEN_HEIGHT));
		for(p.x=x_initial;p.x<max.x;p.x=p.x+ dx){
			//puts("x: ");
			//uart_putint((int)(p.x*SCREEN_WIDTH));
			
			if(inside(p,a,b,c)){
				set_pixelv(framebuffer,(vec2){p.x,p.y},color);
			}
		}
		
	}
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