#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

//Records where exactly we hit on the object
class HitRecord {
public:
	//function list
	/*Point3 getCurrPoint();
	Vec3 getNormal();
	double getParameterT();

	void setCurrPoint(Point3& new_point);
	void setNormal(Vec3& new_normal);
	void setNewParameterT(double new_parameter_t);*/

	void setFaceNormal(const Ray& curr_ray, const Vec3& outward_normal);


public:
	//member list
	Point3 m_curr_point;
	Vec3 m_normal;
	double m_parameter_t;
	bool m_front_face;
};

class Hittable {
public:
	virtual ~Hittable() = default;


	virtual bool isObjectHit(const Ray& curr_ray, const double ray_tmin, const double ray_tmax, HitRecord& record) const = 0;
};

#endif