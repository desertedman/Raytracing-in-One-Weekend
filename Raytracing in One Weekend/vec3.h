#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vec3 {
public:
	Vec3() {
		mXYZ[0] = 0;
		mXYZ[1] = 0;
		mXYZ[2] = 0;
	}

	Vec3(double x, double y, double z) {
		mXYZ[0] = x;
		mXYZ[1] = y;
		mXYZ[2] = z;
	}

	double getX() const {
		return mXYZ[0];
	}

	double getY() const {
		return mXYZ[1];
	}

	double getZ() const {
		return mXYZ[2];
	}

	Vec3 operator-() const {
		return Vec3(-(*this).getX(), -(*this).getY(), -(*this).getZ());
	}

	double operator[](int i) const {
		return mXYZ[i];
	}

	double& operator[](int i) {
		return mXYZ[i];
	}

	Vec3& operator+=(const Vec3& rhs) {
		mXYZ[0] += rhs.getX();
		mXYZ[1] += rhs.getY();
		mXYZ[2] += rhs.getZ();
		return (*this);
	}

	Vec3& operator*=(double t) {
		mXYZ[0] *= t;
		mXYZ[1] *= t;
		mXYZ[2] *= t;
		return (*this);
	}

	Vec3& operator/=(double t) {
		return (*this) *= (1 / t);
	}

	double getLength() const {
		return std::sqrt((*this).getLengthSquared());
	}

	double getLengthSquared() const {
		return (*this).getX() * (*this).getX() + (*this).getY() * (*this).getY() + (*this).getZ() * (*this).getZ();
	}

	bool isNearZero() const {
		//Return true if the vector is close to zero in all dimensions.

		auto s = 1e-8;

		//std::fabs returns absolute value of its input.
		return (std::fabs(mXYZ[0]) < s) && (std::fabs(mXYZ[1]) < s) && (std::fabs(mXYZ[2]) < s);
	}

	static Vec3 getRandomVector() {
		return Vec3(getRandomDouble(), getRandomDouble(), getRandomDouble());
	}

	static Vec3 getRandomVector(double min, double max) {
		return Vec3(getRandomDouble(min, max), getRandomDouble(min, max), getRandomDouble(min, max));
	}

private:
	double mXYZ[3];
};


using Point3 = Vec3;


//Vector Utility Functions

std::ostream& operator<<(std::ostream& out, const Vec3& vector) {
	return out << vector.getX() << ' ' << vector.getY() << ' ' << vector.getZ();
}

inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY(), lhs.getZ() + rhs.getZ());
}

inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY(), lhs.getZ() - rhs.getZ());
}

inline Vec3 operator*(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.getX() * rhs.getX(), lhs.getY() * rhs.getY(), lhs.getZ() * rhs.getZ());
}

inline Vec3 operator*(double lhs, const Vec3& rhs) {
	return Vec3(lhs * rhs.getX(), lhs * rhs.getY(), lhs * rhs.getZ());
}

inline Vec3 operator*(const Vec3& lhs, double rhs) {
	return rhs * lhs;
}

inline Vec3 operator/(const Vec3& lhs, double rhs) {
	return lhs * (1 / rhs);
}

inline double getDotProduct(const Vec3& lhs, const Vec3& rhs) {
	return lhs.getX() * rhs.getX()
		+ lhs.getY() * rhs.getY()
		+ lhs.getZ() * rhs.getZ();
}

inline Vec3 getCrossProduct(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.getY() * rhs.getZ() - lhs.getZ() * rhs.getY(),
		lhs.getZ() * rhs.getX() - lhs.getX() * rhs.getZ(),
		lhs.getX() * rhs.getY() - lhs.getY() * rhs.getX());
}

inline Vec3 getUnitVector(const Vec3& vector) {
	return vector / vector.getLength();
}

// Generate a random vector within the unit sphere.
inline Vec3 generateRandUnitVector() {
	while (true) {
		Vec3 randPoint = Vec3::getRandomVector(-1, 1);
		double lengthSquared = randPoint.getLengthSquared();

		if (1e-16 < lengthSquared && lengthSquared <= 1) {
			return randPoint / sqrt(lengthSquared);
		}
	}
}

inline Vec3 getRandVecOnHemisphere(const Vec3& normal) {
	Vec3 onUnitSphere = generateRandUnitVector();

	if (getDotProduct(onUnitSphere, normal) > 0.0) {
		return onUnitSphere;
	}

	else {
		return -onUnitSphere;
	}

}

inline Vec3 reflectVector(const Vec3& incomingVector, const Vec3& normalVector) {
	return incomingVector - 2 * getDotProduct(incomingVector, normalVector) * normalVector;
}

#endif