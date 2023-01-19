#pragma once
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;
using std::vector;

class hittable_list : public hittable {
public:
	hittable_list(){}
	hittable_list(shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const override;
public:
	vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& record) const {
	
	auto temp_max = t_max;
	hit_record temp_record;
	bool hit_anything = false;
	for (const auto& object : objects) {
		if (object->hit(r, t_min, temp_max, temp_record)) {
			temp_max = temp_record.t;
			record = temp_record;
			hit_anything = true;
		}
	}
		return hit_anything;


}
#endif // !HITTABLE_LIST_H
