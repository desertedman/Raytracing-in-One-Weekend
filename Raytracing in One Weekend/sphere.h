#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"


class Sphere : public Hittable {
public :
	Sphere(const Point3& center, double radius, shared_ptr<Material> material) {
		mCenter = center;
		mRadius = fmax(0, radius);
		mCurrMaterial = material;
	}

	bool isObjectHit(const Ray& curr_ray, Interval ray_t, HitRecord& record) const override {
		Vec3 raycast = mCenter - curr_ray.getOrigin();
		double a = curr_ray.getDirection().getLengthSquared();
		double h = getDotProduct(curr_ray.getDirection(), raycast);
		double c = raycast.getLengthSquared() - mRadius * mRadius;

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
		//P(t) = O + tD
		//Use parameter t to calculate final position of sphere intersection
		record.parameterT = root_t;
		record.currPoint = curr_ray.getPosition(record.parameterT);


		//Normal vector = unit vector of (Point of intersection - center of sphere)
		Vec3 outward_normal = (record.currPoint - mCenter) / mRadius;
		record.setFaceNormal(curr_ray, outward_normal);


		record.currMaterial = (*this).mCurrMaterial;

		return true;
	}


private:
	Point3 mCenter;
	double mRadius;
	shared_ptr<Material> mCurrMaterial;
};

#endif