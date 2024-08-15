#include "hittable.h"

//Point3 HitRecord::getCurrPoint() {
//	return (*this).m_curr_point;
//}
//
//Vec3 HitRecord::getNormal() {
//	return (*this).m_normal;
//}
//
//double HitRecord::getParameterT() {
//	return (*this).m_parameter_t;
//}
//
//void HitRecord::setCurrPoint(Point3& new_point) {
//	(*this).m_curr_point = new_point;
//}
//
//void HitRecord::setNormal(Vec3& new_normal) {
//	(*this).m_normal = new_normal;
//}
//
//void HitRecord::setNewParameterT(double new_parameter_t) {
//	(*this).m_parameter_t = new_parameter_t;
//}

void HitRecord::setFaceNormal(const Ray& curr_ray, const Vec3& outward_normal) {
	//Sets the hit record normal vector.
	//Note: the parameter 'outward_normal' is assumed to have unit length.

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