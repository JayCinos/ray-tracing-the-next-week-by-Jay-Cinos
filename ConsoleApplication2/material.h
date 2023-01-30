#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"


class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
	lambertian(const color& a): albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		auto scttered_direction = rec.normal + random_in_unit_sphere();
		if (scttered_direction.near_zero()) {
			scttered_direction = rec.normal;
		}
		scattered = ray(rec.p, scttered_direction);
		attenuation = albedo;
		return true;
	}
public:
	color albedo;
};

vec3 reflection(const ray& ray_in, const hit_record& rec) {
	vec3 ref;
	vec3 b;
	b =  dot(rec.normal, ray_in.direction()) * rec.normal;
	ref =  ray_in.direction() - 2 * b;
	return ref;
}

class metal : public material {
public:
	metal(const color& a,const double& f): albedo(a), fuzz(f) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		auto scttered_direction = reflection(r_in, rec);
		scattered = ray(rec.p, scttered_direction + fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return dot(scttered_direction , rec.normal)> 0;
	}
public:
	color albedo;
	double fuzz;
};

class dieletric : public material {
public:
	dieletric(const color& a,const double& r): albedo(a), refraction_index(r) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		
		double refraction_ratio = rec.front_face ? ( b1.0 / refraction_index) : refraction_index;

		vec3 unit_rayin = unit_vector(r_in.direction());
		auto scttered_direction = refract(unit_rayin, rec.normal, refraction_ratio);
		
		scattered = ray(rec.p, scttered_direction);
		// scattered = ray(rec.p, scttered_direction + fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return true;
	}
public:
	color albedo;
	// double fuzz;
	double refraction_index;
};
#endif
