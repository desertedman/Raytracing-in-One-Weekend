#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class HitRecord {
public: 
	/*Point3 getCurrPoint();
	Vec3 getNormal();
	double getParameterT();

	void setCurrPoint(Point3& new_point);
	void setNormal(Vec3& new_normal);
	void setNewParameterT(double new_parameter_t);*/

	Point3 m_curr_point;
	Vec3 m_normal;
	double m_parameter_t;
private:
	
};

class Hittable {
public:
	virtual ~Hittable() = default;


	virtual bool hit(const Ray& curr_ray, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};

#endif