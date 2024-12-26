#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>


class HittableList : public Hittable {
public:
	HittableList() {}
	HittableList(shared_ptr<Hittable> currObject) {
		addObject(currObject);
	}

	void clearList() {
		(*this).mObjects.clear();
	}

	void addObject(shared_ptr<Hittable> currObject) {
		(*this).mObjects.push_back(currObject);
	}

	bool isObjectHit(const Ray& currRay, Interval rayT, HitRecord& record) const override {
		HitRecord tempRecord;
		bool hitAnything = false;
		double closestIntersectionSoFar = rayT.getMax();


		//vector iterators
		//TODO: figure out how to rewrite this in terms of for (i = 0; i != end; i++)
		for (const auto& currObj : mObjects) {
			if ((*currObj).isObjectHit(currRay, Interval(rayT.getMin(), closestIntersectionSoFar), tempRecord)) {
				hitAnything = true;
				closestIntersectionSoFar = tempRecord.parameterT;
				record = tempRecord;
			}
		}

		return hitAnything;
	}

private:
	//member list
	std::vector<shared_ptr<Hittable>> mObjects;	//what is a shared_ptr?
};

#endif