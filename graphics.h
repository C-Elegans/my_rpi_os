//
//  graphics.h
//  my_rpi_os
//
//  Created by Michael Nolan on 2/6/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#ifndef graphics_h
#define graphics_h
#include "vector.h"
void set_pixel(short* framebuffer, int x, int y, short color);
void line(short* framebuffer, ivec2 a,ivec2 b, short color);
void triangle(short* framebuffer,ivec2 a, ivec2 b, ivec2 c, short color);
void set_pixelv(short* framebuffer, vec2 p, short color);
#endif /* graphics_h */
