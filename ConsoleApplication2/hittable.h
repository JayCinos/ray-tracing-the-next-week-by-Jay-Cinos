#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H
#include "ray.h"

class material;

struct hit_record {
	double t;
	point3 p;
	vec3 normal;
	bool front_face;
	shared_ptr<material> mat_ptr;

	inline void set_front_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(outward_normal, r.direction()) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const = 0;
};

#endif // !HITTABLE_H
