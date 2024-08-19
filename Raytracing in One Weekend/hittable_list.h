#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "rtweekend.h"
#include "hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;


class HittableList : public Hittable {
public:
	HittableList();
	HittableList(shared_ptr<Hittable> curr_object);

	void clearList();

	void addObject(shared_ptr<Hittable> curr_object);

	bool isObjectHit(const Ray& curr_ray, const double ray_tmin, const double ray_tmax, HitRecord& record) const override;

private:
	//member list
	std::vector<shared_ptr<Hittable>> m_objects;	//what is a shared_ptr?
};

#endif