#ifndef RAY_H
#define RAY_H

#include "vec3.h"


class Ray {
public:
	Ray() = default;
	Ray(const Point3& origin, const Vec3& direction) {
		(*this).mOrigin = origin;
		(*this).mDirection = direction;
	}

	const Point3& getOrigin() const {
		return mOrigin;
	}
	const Vec3& getDirection() const {
		return mDirection;
	}

	Point3 getPosition(double parameter_t) const {
		return (*this).getOrigin() + parameter_t * (*this).getDirection();
	}

private:
	Point3 mOrigin;
	Vec3 mDirection;
};

#endif