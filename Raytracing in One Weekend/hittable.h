#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
//#include "interval.h"


//Records where exactly we hit on the object
class HitRecord {
public:
	void setFaceNormal(const Ray& curr_ray, const Vec3& outward_normal);


public:
	//member list
	Point3 m_curr_point;
	Vec3 m_normal;
	double m_parameter_t = 0;
	bool m_front_face = false;


};

class Hittable {
public:
	virtual ~Hittable() = default;


	virtual bool isObjectHit(const Ray& curr_ray, const double ray_tmin, const double ray_tmax, HitRecord& record) const = 0;
};

#endif