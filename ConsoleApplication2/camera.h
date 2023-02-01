#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
class camera {
public:
	camera(point3 pointfrom, 
			point3 pointat,
			vec3 cam_up,
			double fov, 
			double aspect_ratio,
			double aperture,
			double focus_dist){
		
		auto theta = degrees_to_radians(fov);
		auto h = tan(theta/2 );
		auto view_height = 2 * h;
		auto view_width = aspect_ratio * view_height;

		w = unit_vector(pointfrom -  pointat);
		u = unit_vector(cross(cam_up, w));
		v = cross(w, u);

		horizion = focus_dist*view_width * u;
		vertical = focus_dist*view_height * v;

		origin = pointfrom;
		lower_left_cornor = origin - horizion / 2 - vertical / 2  -  focus_dist* w;
		lens_radius = aperture / 2;
	}
	ray get_ray(double u_1, const double v_1) const{
			auto rd =lens_radius * random_in_unit_disk();
			auto offset = rd.x() * u + rd.y() * v;


			return ray(origin + offset, lower_left_cornor + u_1 * horizion  + v_1 * vertical - origin- offset);
		}
public:
	point3 origin;
	vec3 horizion;
	vec3 vertical;
	vec3 u,v,w;
	point3 lower_left_cornor;
	double lens_radius;

};

#endif // !CAMERA_H
