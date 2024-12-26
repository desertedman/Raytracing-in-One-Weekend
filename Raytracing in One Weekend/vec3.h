#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vec3 {
public:
	Vec3() {
		m_XYZ[0] = 0;
		m_XYZ[1] = 0;
		m_XYZ[2] = 0;
	}

	Vec3(double x, double y, double z) {
		m_XYZ[0] = x;
		m_XYZ[1] = y;
		m_XYZ[2] = z;
	}

	double getX() const {
		return m_XYZ[0];
	}

	double getY() const {
		return m_XYZ[1];
	}

	double getZ() const {
		return m_XYZ[2];
	}

	Vec3 operator-() const {
		return Vec3(-(*this).getX(), -(*this).getY(), -(*this).getZ());
	}

	double operator[](int i) const {
		return m_XYZ[i];
	}

	double& operator[](int i) {
		return m_XYZ[i];
	}

	Vec3& operator+=(const Vec3& rhs) {
		m_XYZ[0] += rhs.getX();
		m_XYZ[1] += rhs.getY();
		m_XYZ[2] += rhs.getZ();
		return (*this);
	}

	Vec3& operator*=(double t) {
		m_XYZ[0] *= t;
		m_XYZ[1] *= t;
		m_XYZ[2] *= t;
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
		return (std::fabs(m_XYZ[0]) < s) && (std::fabs(m_XYZ[1]) < s) && (std::fabs(m_XYZ[2]) < s);
	}

	static Vec3 getRandomVector() {
		return Vec3(getRandomDouble(), getRandomDouble(), getRandomDouble());
	}

	static Vec3 getRandomVector(double min, double max) {
		return Vec3(getRandomDouble(min, max), getRandomDouble(min, max), getRandomDouble(min, max));
	}

private:
	double m_XYZ[3];
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
		Vec3 rand_point = Vec3::getRandomVector(-1, 1);
		double length_squared = rand_point.getLengthSquared();

		if (1e-16 < length_squared && length_squared <= 1) {
			return rand_point / sqrt(length_squared);
		}
	}
}

inline Vec3 getRandVecOnHemisphere(const Vec3& normal) {
	Vec3 on_unit_sphere = generateRandUnitVector();

	if (getDotProduct(on_unit_sphere, normal) > 0.0) {
		return on_unit_sphere;
	}

	else {
		return -on_unit_sphere;
	}

}

inline Vec3 reflectVector(const Vec3& incoming_vector, const Vec3& normal_vector) {
	return incoming_vector - 2 * getDotProduct(incoming_vector, normal_vector) * normal_vector;
}

#endif