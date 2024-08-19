#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
public :
	Sphere(const Point3& center, double radius) {
		(*this).m_center = center;
		(*this).m_radius = fmax(0, radius);
	}

	bool isObjectHit(const Ray& curr_ray, const double ray_tmin, const double ray_tmax, HitRecord& record) const override {
		Vec3 raycast = (*this).m_center - curr_ray.getOrigin();
		double a = curr_ray.getDirection().getLengthSquared();
		double h = dot(curr_ray.getDirection(), raycast);
		double c = raycast.getLengthSquared() - (*this).m_radius * (*this).m_radius;

		double discriminant = h * h - a * c;
		if (discriminant < 0) {
			return false;
		}

		double sqrt_discriminant = sqrt(discriminant);

		//Find the nearest root that lies in the acceptable range.
		// t = [h +/- sqrt(D)] / a
		//Assume closest point of intersection first.
		double root_t = (h - sqrt_discriminant) / a;


		//If closest root is out of range, t_min < t < t_max, check positive root.
		if (root_t <= ray_tmin || ray_tmax <= root_t) {
			root_t = (h + sqrt_discriminant) / a;


			//If positive root still out of range, then we haven't hit object
			if (root_t <= ray_tmin || ray_tmax <= root_t) {
				return false;
			}
		}


		//Record where exactly we hit
		record.m_parameter_t = root_t;

		//P(t) = O + tD
		//Use parameter t to calculate final position of sphere intersection
		record.m_curr_point = curr_ray.getPosition(record.m_parameter_t);

		//Normal vector = unit vector of (Point of intersection - center of sphere)
		Vec3 outward_normal = (record.m_curr_point - (*this).m_center) / (*this).m_radius;
		record.setFaceNormal(curr_ray, outward_normal);

		return true;
	}


private:
	Point3 m_center;
	double m_radius;
};

#endif