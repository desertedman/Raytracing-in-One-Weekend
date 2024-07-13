#ifndef RAY_H
#define RAY_H

#include "vec3.h"


class Ray {
public:
	Ray();
	Ray(const Point3& origin, const Vec3& direction);

	const Point3& getOrigin() const;
	const Vec3& getDirection() const;

	Point3 getPosition(double t) const;

private:
	Point3 m_origin;
	Vec3 m_direction;
};

#endif