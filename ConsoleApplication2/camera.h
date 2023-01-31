#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
class camera {
public:
	camera(double fov, double aspect_ratio){
		
		auto theta = degrees_to_radians(fov);
		auto h = tan(theta/2 );
		auto view_height = 2 * h;
		auto view_width = aspect_ratio * view_height;
		auto focal_length = 1.0;
		
		origin = point3(0, 0, 0);
		horizion = vec3(view_width, 0, 0);
		vertical = vec3(0, view_height, 0);
		lower_left_cornor = origin - horizion/2 - vertical/2 - vec3(0, 0, focal_length);

	}
	ray get_ray(double u, const double v) const{
			return ray(origin, lower_left_cornor + u*horizion + v*vertical - origin);
		}
public:
	point3 origin;
	vec3 horizion;
	vec3 vertical;
	point3 lower_left_cornor;

};

#endif // !CAMERA_H
