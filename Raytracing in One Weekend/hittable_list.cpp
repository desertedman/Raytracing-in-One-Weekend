#include "hittable_list.h"

HittableList::HittableList() {

}

HittableList::HittableList(shared_ptr<Hittable> curr_object) {
	addObject(curr_object);
}

void HittableList::clearList() {
	(*this).m_objects.clear();
}

void HittableList::addObject(shared_ptr<Hittable> curr_object) {
	(*this).m_objects.push_back(curr_object);
}

bool HittableList::isObjectHit(const Ray& curr_ray, const double ray_tmin, const double ray_tmax, HitRecord& record) const {
	HitRecord temp_record;
	bool hit_anything = false;
	auto closest_so_far = ray_tmax;


	//vector iterators
	//TODO: figure out how to rewrite this in terms of for (i = 0; i != end; i++)
	for (const auto& curr_obj : (*this).m_objects) {
		if ((*curr_obj).isObjectHit(curr_ray, ray_tmin, closest_so_far, temp_record)) {
			hit_anything = true;
			closest_so_far = temp_record.m_parameter_t;
			record = temp_record;
		}
	}

	return hit_anything;
}