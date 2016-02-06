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