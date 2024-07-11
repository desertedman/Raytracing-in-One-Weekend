#include "ray.h"

ray::ray() {
	//nothing
}

ray::ray(const point3& origin, const vec3& direction) {
	(*this).origin = origin;
	(*this).direction = direction;
}

const point3& ray::getOrigin() const {
	return (*this).origin;
}

const vec3& ray::getDirection() const {
	return (*this).direction;
}

point3 ray::at(double t) const {
	return (*this).origin + t * (*this).direction;
}