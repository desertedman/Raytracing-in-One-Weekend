#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
public :
	Sphere(const Point3& center, double radius);

	bool hit(const Ray& curr_ray, const double ray_tmin, const double ray_tmax, HitRecord& record) const override;


private:
	Point3 m_center;
	double m_radius;
};

#endif