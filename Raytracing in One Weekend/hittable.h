#ifndef HITTABLE_H
#define HITTABLE_H


//Records where exactly we hit on the object
class HitRecord {
public:
	void setFaceNormal(const Ray& curr_ray, const Vec3& outward_normal) {
		//Sets the hit record normal vector.
		//Note: the parameter 'outward_normal' is assumed to have unit length.

		//Dot product: |A||B|cos(theta)
		//If rays are opposite each other, then theta > 90 degrees; dot product will be negative
		//If rays are same direction, then theta < 90 degrees; dot product will be positive


		if (dot(curr_ray.getDirection(), outward_normal) > 0.0) {
			//ray is inside the sphere
			(*this).m_normal = -outward_normal;
			(*this).m_front_face = false;
		}

		else {
			//ray is outside the sphere
			(*this).m_normal = outward_normal;
			(*this).m_front_face = true;
		}
	}


public:
	//member list
	Point3 m_curr_point;
	Vec3 m_normal;
	double m_parameter_t = 0;
	bool m_front_face = false;


};

class Hittable {
public:
	virtual ~Hittable() = default;


	virtual bool isObjectHit(const Ray& curr_ray, Interval ray_t, HitRecord& record) const = 0;
};

#endif