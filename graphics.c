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
void line(short* framebuffer, ivec2 a, ivec2 b, short color){
	int x0 = a.x;
	int x1 = b.x;
	int y0 = a.y;
	int y1 = b.y;
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
int inside(ivec2 p, ivec2 a, ivec2 b, ivec2 c){
	vec2 vp=(vec2){(float)p.x,(float)p.y};
	vec2 va=(vec2){(float)a.x,(float)a.y};
	vec2 vb=(vec2){(float)b.x,(float)b.y};
	vec2 vc=(vec2){(float)c.x,(float)c.y};
	return same_side(vp,va,vb,vc) && same_side(vp,vb,vc,va) && same_side(vp,vc,va,vb);
}

void triangle(short* framebuffer,ivec2 a, ivec2 b, ivec2 c, short color){
	ivec2 p, max;
	
	p.x = fmin(a.x,b.x);
	p.x = fmin(p.x,c.x);
	p.y = fmin(a.y,b.y);
	p.y = fmin(p.y,c.y);
	
	max.x = fmax(a.x,b.x);
	max.x = fmax(p.x,c.x);
	max.y = fmax(a.y,b.y);
	max.y = fmax(p.y,c.y);
	int x_initial = p.x;
	for(;p.y<max.y;p.y++){
		
		for(p.x=x_initial;p.x<max.x;p.x++){
			
			
			if(inside(p,a,b,c)){
				set_pixel(framebuffer,p.x,p.y,color);
			}
		}
		
	}
}
