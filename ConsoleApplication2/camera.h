#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
class camera {
public:
	camera(point3 pointfrom, 
			point3 pointat,
			vec3 cam_up,
			double fov, double aspect_ratio){
		
		auto theta = degrees_to_radians(fov);
		auto h = tan(theta/2 );
		auto view_height = 2 * h;
		auto view_width = aspect_ratio * view_height;

		auto w = unit_vector(pointfrom -  pointat);
		auto u = unit_vector(cross(cam_up, w));
		auto v = cross(w, u);

		horizion = view_width * u;
		vertical = view_height * v;

		origin = pointfrom;
		lower_left_cornor = origin - horizion / 2 - vertical / 2  -  w;

	}
	ray get_ray(double u_1, const double v_1) const{
			return ray(origin, lower_left_cornor + u_1 * horizion  + v_1 * vertical - origin);
		}
public:
	point3 origin;
	vec3 horizion;
	vec3 vertical;
	point3 lower_left_cornor;

};

#endif // !CAMERA_H
