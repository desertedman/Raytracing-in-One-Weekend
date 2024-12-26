#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"


class Triangle : public Hittable {
public:
	Triangle(const Point3& inputA, const Point3& inputB, const Point3& inputC, shared_ptr<Material> material) {
		mVertex0 = inputA;
		mVertex1 = inputB;
		mVertex2 = inputC;
		mCurrMaterial = material;
	}

	bool isObjectHit(const Ray& currRay, Interval rayT, HitRecord& record) const override {
		Vec3 A = mVertex1 - mVertex0;
		Vec3 B = mVertex2 - mVertex0;
		Vec3 C = getCrossProduct(A, B);		
		Vec3 outwardNormal = getUnitVector(C);

		//Set normal to be facing the correct direction; we want normals to point towards incoming ray
		record.setFaceNormal(currRay, outwardNormal);



		record.currMaterial = (*this).mCurrMaterial;

		return false;
	}

private:
	Point3 mVertex0;
	Point3 mVertex1;
	Point3 mVertex2;
	shared_ptr<Material> mCurrMaterial;
};

#endif