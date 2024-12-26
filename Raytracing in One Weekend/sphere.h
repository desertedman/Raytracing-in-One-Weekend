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

	bool isObjectHit(const Ray& currRay, Interval rayT, HitRecord& record) const override {
		Vec3 raycast = mCenter - currRay.getOrigin();
		double a = currRay.getDirection().getLengthSquared();
		double h = getDotProduct(currRay.getDirection(), raycast);
		double c = raycast.getLengthSquared() - mRadius * mRadius;

		double discriminant = h * h - a * c;
		if (discriminant < 0) {
			return false;
		}

		double sqrtDiscriminant = sqrt(discriminant);

		//Find the nearest root that lies in the acceptable range.
		// t = [h +/- sqrt(D)] / a
		//Assume closest point of intersection first.
		double rootT = (h - sqrtDiscriminant) / a;


		//If closest root is out of range, t_min < t < t_max, check positive root.
		if (!rayT.surroundsInterval(rootT)) {
			rootT = (h + sqrtDiscriminant) / a;


			//If positive root still out of range, then we haven't hit object
			if (!rayT.surroundsInterval(rootT)) {
				return false;
			}
		}


		//Record where exactly we hit
		//P(t) = O + tD
		//Use parameter t to calculate final position of sphere intersection
		record.parameterT = rootT;
		record.currPoint = currRay.getPosition(record.parameterT);


		//Normal vector = unit vector of (Point of intersection - center of sphere)
		Vec3 outwardNormal = (record.currPoint - mCenter) / mRadius;
		record.setFaceNormal(currRay, outwardNormal);


		record.currMaterial = (*this).mCurrMaterial;

		return true;
	}


private:
	Point3 mCenter;
	double mRadius;
	shared_ptr<Material> mCurrMaterial;
};

#endif