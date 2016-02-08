//
//  vector.c
//  my_rpi_os
//
//  Created by Michael Nolan on 2/6/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#include "vector.h"
float cross2(vec2 a, vec2 b){
	return (a.x*b.y)-(a.y*b.x);
}
vec2 add(vec2 a, vec2 b){
	return (vec2){a.x+b.x,a.y+b.y};
}
vec2 sub(vec2 a, vec2 b){
	return (vec2){a.x-b.x,a.y-b.y};
}
float dot(vec2 a,vec2 b){
	return a.x*b.x+a.y*b.y;
}
int icross2(ivec2 a, ivec2 b){
	return (int)((float)a.x*(float)b.y)-((float)a.y*(float)b.x);
}
ivec2 iadd(ivec2 a, ivec2 b){
	return (ivec2){a.x+b.x,a.y+b.y};
}
ivec2 isub(ivec2 a, ivec2 b){
	return (ivec2){a.x-b.x,a.y-b.y};
}
int idot(ivec2 a,ivec2 b){
	return (int)((float)a.x*(float)b.x+(float)a.y*(float)b.y);
}