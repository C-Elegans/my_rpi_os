//
//  vector.h
//  my_rpi_os
//
//  Created by Michael Nolan on 2/6/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//

#ifndef vector_h
#define vector_h
typedef struct{
	float x;
	float y;
	float z;
}vec3;
typedef struct{
	float x;
	float y;
}vec2;
float cross2(vec2 a, vec2 b);
vec2 add(vec2 a, vec2 b);
vec2 sub(vec2 a, vec2 b);
float dot(vec2 a,vec2 b);
#endif /* vector_h */
