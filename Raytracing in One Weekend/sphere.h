#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"


class Sphere : public Hittable {
public :
	Sphere(const Point3& center, double radius) {
		m_Center = center;
		m_Radius = fmax(0, radius);
	}

	bool isObjectHit(const Ray& curr_ray, Interval ray_t, HitRecord& record) const override {
		Vec3 raycast = m_Center - curr_ray.getOrigin();
		double a = curr_ray.getDirection().getLengthSquared();
		double h = getDotProduct(curr_ray.getDirection(), raycast);
		double c = raycast.getLengthSquared() - m_Radius * m_Radius;

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
		if (!ray_t.surroundsInterval(root_t)) {
			root_t = (h + sqrt_discriminant) / a;


			//If positive root still out of range, then we haven't hit object
			if (!ray_t.surroundsInterval(root_t)) {
				return false;
			}
		}


		//Record where exactly we hit
		record.m_parameter_t = root_t;

		//P(t) = O + tD
		//Use parameter t to calculate final position of sphere intersection
		record.m_curr_point = curr_ray.getPosition(record.m_parameter_t);

		//Normal vector = unit vector of (Point of intersection - center of sphere)
		Vec3 outward_normal = (record.m_curr_point - m_Center) / m_Radius;
		record.setFaceNormal(curr_ray, outward_normal);

		return true;
	}


private:
	Point3 m_Center;
	double m_Radius;
};

#endif