#include "vec3.h"
#include <cmath>


Vec3::Vec3() {
	(*this).m_xyz[0] = 0;				//we cant set whole array equal to 0, 0, 0 directly so we have to access each individual element
	(*this).m_xyz[1] = 0;
	(*this).m_xyz[2] = 0;
}

Vec3::Vec3(double x, double y, double z) {
	(*this).m_xyz[0] = x;
	(*this).m_xyz[1] = y;
	(*this).m_xyz[2] = z;
}

double Vec3::getX() const {
	return (*this).m_xyz[0];
}

double Vec3::getY() const {
	return (*this).m_xyz[1];
}

double Vec3::getZ() const {
	return (*this).m_xyz[2];
}

Vec3 Vec3::operator-() const {
	return Vec3(-(*this).getX(), -(*this).getY(), -(*this).getZ());
}

double Vec3::operator[](int i) const {
	return (*this).m_xyz[i];
}

/*
double& Vec3::operator[](int i) const {
	return (*this).m_xyz[i];
}
*/

Vec3& Vec3::operator+=(const Vec3& rhs) {
	(*this).m_xyz[0] += rhs.getX();
	(*this).m_xyz[1] += rhs.getY();
	(*this).m_xyz[2] += rhs.getZ();
	return (*this);
}

Vec3& Vec3::operator*=(double t) {
	(*this).m_xyz[0] *= t;
	(*this).m_xyz[1] *= t;
	(*this).m_xyz[2] *= t;
	return (*this);
}

Vec3& Vec3::operator/=(double t) {
	return (*this) *= (1 / t);
}

double Vec3::getLength() const {
	return std::sqrt((*this).getLengthSquared());
}

double Vec3::getLengthSquared() const {
	return (*this).getX() * (*this).getX() + (*this).getY() * (*this).getY() + (*this).getZ() * (*this).getZ();
}

//Vector Utility Functions

std::ostream& operator<<(std::ostream& out, const Vec3& vector) {
	return out << vector.getX() << ' ' << vector.getY() << ' ' << vector.getZ();
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY(), lhs.getZ() + rhs.getZ());
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY(), lhs.getZ() - rhs.getZ());
}

Vec3 operator*(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.getX() * rhs.getX(), lhs.getY() * rhs.getY(), lhs.getZ() * rhs.getZ());
}

Vec3 operator*(double lhs, const Vec3& rhs) {
	return Vec3(lhs * rhs.getX(), lhs * rhs.getY(), lhs * rhs.getZ());
}

Vec3 operator*(const Vec3& lhs, double rhs) {
	return rhs * lhs;
}

Vec3 operator/(const Vec3& lhs, double rhs) {
	return lhs * (1 / rhs);
}

double dot(const Vec3& lhs, const Vec3& rhs) {
	return lhs.getX() * rhs.getX()
		+ lhs.getY() * rhs.getY()
		+ lhs.getZ() * rhs.getZ();
}

Vec3 cross(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.getY() * rhs.getZ() - lhs.getZ() * rhs.getY(),
		lhs.getZ() * rhs.getX() - lhs.getX() * rhs.getZ(),
		lhs.getX() * rhs.getY() - lhs.getY() * rhs.getX());
}

Vec3 unitVector(const Vec3& vector) {
	return vector / vector.getLength();
}