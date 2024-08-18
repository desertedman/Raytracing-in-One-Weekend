#include "ray.h"

Ray::Ray() {
	//nothing
}

Ray::Ray(const Point3& origin, const Vec3& direction) {
	(*this).m_origin = origin;
	(*this).m_direction = direction;
}

const Point3& Ray::getOrigin() const {
	return (*this).m_origin;
}

const Vec3& Ray::getDirection() const {
	return (*this).m_direction;
}

Point3 Ray::getPosition(double parameter_t) const {
	return (*this).getOrigin() + parameter_t * (*this).getDirection();
}
