#ifndef RAY_H
#define RAY_H

#include "vec3.h"


class Ray {
public:
	Ray() = default;
	Ray(const Point3& origin, const Vec3& direction) {
		(*this).m_Origin = origin;
		(*this).m_Direction = direction;
	}

	const Point3& getOrigin() const {
		return m_Origin;
	}
	const Vec3& getDirection() const {
		return m_Direction;
	}

	Point3 getPosition(double parameter_t) const {
		return (*this).getOrigin() + parameter_t * (*this).getDirection();
	}

private:
	Point3 m_Origin;
	Vec3 m_Direction;
};

#endif