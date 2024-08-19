#include "hittable.h"


void HitRecord::setFaceNormal(const Ray& curr_ray, const Vec3& outward_normal) {
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