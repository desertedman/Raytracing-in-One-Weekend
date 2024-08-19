#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>


class HittableList : public Hittable {
public:
	HittableList() {}
	HittableList(shared_ptr<Hittable> curr_object) {
		addObject(curr_object);
	}

	void clearList() {
		(*this).m_objects.clear();
	}

	void addObject(shared_ptr<Hittable> curr_object) {
		(*this).m_objects.push_back(curr_object);
	}

	bool isObjectHit(const Ray& curr_ray, Interval ray_t, HitRecord& record) const override {
		HitRecord temp_record;
		bool hit_anything = false;
		double closest_intersection_so_far = ray_t.getMax();


		//vector iterators
		//TODO: figure out how to rewrite this in terms of for (i = 0; i != end; i++)
		for (const auto& curr_obj : (*this).m_objects) {
			if ((*curr_obj).isObjectHit(curr_ray, Interval(ray_t.getMin(), closest_intersection_so_far), temp_record)) {
				hit_anything = true;
				closest_intersection_so_far = temp_record.m_parameter_t;
				record = temp_record;
			}
		}

		return hit_anything;
	}

private:
	//member list
	std::vector<shared_ptr<Hittable>> m_objects;	//what is a shared_ptr?
};

#endif