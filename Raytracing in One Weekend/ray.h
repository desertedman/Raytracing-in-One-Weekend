#ifndef RAY_H
#define RAY_H

#include "vec3.h"


class Ray {
public:
	Ray();
	Ray(const Point3& origin, const Vec3& direction) {
		(*this).m_origin = origin;
		(*this).m_direction = direction;
	}

	const Point3& getOrigin() const {
		return (*this).m_origin;
	}
	const Vec3& getDirection() const {
		return (*this).m_direction;
	}

	Point3 getPosition(double parameter_t) const {
		return (*this).getOrigin() + parameter_t * (*this).getDirection();
	}

private:
	Point3 m_origin;
	Vec3 m_direction;
};

#endif