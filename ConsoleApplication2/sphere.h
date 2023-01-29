#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
public:
	sphere() {}
    sphere(point3 orig, double r, shared_ptr<material> m) : origin(orig), radius(r), mat_ptr(m) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const override;

public:
	point3 origin;
	double radius;
    shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& record) const {
    vec3 oc = r.origin() - origin;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    }
    
    auto sqrtd = sqrt(discriminant);

    //find the nerest root that lies in the acceptable range

    auto root = (-b - sqrt(discriminant)) / (2.0 * a);
    if (root < t_min || root > t_max) {
        root = (-b + sqrt(discriminant)) / (2.0 * a);
        if (root < t_min || root > t_max) {
            return false;
        }
    }

    record.t = root;
    record.p = r.at(root);
    vec3 outward_normal = (record.p - origin) / radius;
    record.set_front_normal(r, outward_normal);
    record.mat_ptr = mat_ptr;
}

#endif // !SPHERE_H
