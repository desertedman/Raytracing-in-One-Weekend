#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
public :
	Sphere(const Point3& center, double radius);

	bool hit(const Ray& curr_ray, double ray_tmin, double ray_tmax, HitRecord& rec) const override;


private:
	Point3 center;
	double radius;
};

#endif