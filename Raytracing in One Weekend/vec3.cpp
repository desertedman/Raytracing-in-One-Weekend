#include "vec3.h"
#include <cmath>

using namespace std;

vec3::vec3() {
	(*this).xyz[0] = 0;				//we cant set whole array equal to 0, 0, 0 directly so we have to access each individual element
	(*this).xyz[1] = 0;
	(*this).xyz[2] = 0;
}

vec3::vec3(double x, double y, double z) {
	(*this).xyz[0] = x;
	(*this).xyz[1] = y;
	(*this).xyz[2] = z;
}

double vec3::getX() const {
	return (*this).xyz[0];
}

double vec3::getY() const {
	return (*this).xyz[1];
}

double vec3::getZ() const {
	return (*this).xyz[2];
}

vec3 vec3::operator-() const {
	return vec3(-(*this).getX(), -(*this).getY(), -(*this).getZ());
}

double vec3::operator[](int i) const {
	return (*this).xyz[i];
}

/*
double& vec3::operator[](int i) const {
	return (*this).xyz[i];
}
*/

vec3& vec3::operator+=(const vec3& rhs) {
	(*this).xyz[0] += rhs.getX();
	(*this).xyz[1] += rhs.getY();
	(*this).xyz[2] += rhs.getZ();
	return (*this);
}

vec3& vec3::operator*=(double t) {
	(*this).xyz[0] *= t;
	(*this).xyz[1] *= t;
	(*this).xyz[2] *= t;
	return (*this);
}

vec3& vec3::operator/=(double t) {
	return (*this) *= (1 / t);
}

double vec3::getLength() const {
	return sqrt((*this).getLengthSquared());
}

double vec3::getLengthSquared() const {
	return (*this).getX() * (*this).getX() + (*this).getY() * (*this).getY() + (*this).getZ() * (*this).getZ();
}

//Vector Utility Functions

std::ostream& operator<<(std::ostream& out, const vec3& vector) {
	return out << vector.getX() << ' ' << vector.getY() << ' ' << vector.getZ();
}

vec3 operator+(const vec3& lhs, const vec3& rhs) {
	return vec3(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY(), lhs.getZ() + rhs.getZ());
}

vec3 operator-(const vec3& lhs, const vec3& rhs) {
	return vec3(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY(), lhs.getZ() - rhs.getZ());
}

vec3 operator*(const vec3& lhs, const vec3& rhs) {
	return vec3(lhs.getX() * rhs.getX(), lhs.getY() * rhs.getY(), lhs.getZ() * rhs.getZ());
}

vec3 operator*(double lhs, const vec3& rhs) {
	return vec3(lhs * rhs.getX(), lhs * rhs.getY(), lhs * rhs.getZ());
}

vec3 operator*(const vec3& lhs, double rhs) {
	return rhs * lhs;
}

vec3 operator/(const vec3& lhs, double rhs) {
	return lhs * (1 / rhs);
}

double dot(const vec3& lhs, const vec3& rhs) {
	return lhs.getX() * rhs.getX()
		+ lhs.getY() * rhs.getY()
		+ lhs.getZ() * rhs.getZ();
}

vec3 cross(const vec3& lhs, const vec3& rhs) {
	return vec3(lhs.getY() * rhs.getZ() - lhs.getZ() * rhs.getY(),
		lhs.getZ() * rhs.getX() - lhs.getX() * rhs.getZ(),
		lhs.getX() * rhs.getY() - lhs.getY() * rhs.getX());
}

vec3 unit_vector(const vec3& vector) {
	return vector / vector.getLength();
}