#ifndef HITTABLE_H
#define HITTABLE_H


class Material;


//Records where exactly we hit on the object
class HitRecord {
public:
	void setFaceNormal(const Ray& currRay, const Vec3& outwardNormal) {
		//Sets the hit record normal vector.
		//Note: the parameter 'outwardNormal' is assumed to have unit length.


		//Dot product: |A||B|cos(theta)
		//If rays are opposite each other, then theta > 90 degrees; dot product will be negative
		//If rays are same direction, then theta < 90 degrees; dot product will be positive

		if (getDotProduct(currRay.getDirection(), outwardNormal) > 0.0) {
			//ray is inside the sphere
			(*this).normal = -outwardNormal;
			(*this).frontFace = false;
		}

		else {
			//ray is outside the sphere
			(*this).normal = outwardNormal;
			(*this).frontFace = true;
		}
	}


public:
	//member list
	Point3 currPoint;
	Vec3 normal;
	double parameterT = 0;
	bool frontFace = false;
	shared_ptr<Material> currMaterial;

};

class Hittable {
public:
	virtual ~Hittable() = default;


	virtual bool isObjectHit(const Ray& currRay, Interval rayT, HitRecord& record) const = 0;
};

#endif