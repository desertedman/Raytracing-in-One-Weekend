#ifndef VEC3_H
#define VEC3_H

#include <iostream>


class Vec3 {
public:
	Vec3();
	Vec3(double x, double y, double z);

	double getX() const;
	double getY() const;
	double getZ() const;

	Vec3 operator-() const;
	double operator[](int i) const;
	//double& operator[](int i) const;	
	// i dont know why this doesnt work if i seperate the function definition from declaration
	double& operator[](int i) { return m_xyz[i]; }

	Vec3& operator+=(const Vec3& rhs);
	Vec3& operator*=(double t);
	Vec3& operator/=(double t);

	double getLength() const;
	double getLengthSquared() const;

private:
	double m_xyz[3];
};


using Point3 = Vec3;


//Vector Utility Functions

std::ostream& operator<<(std::ostream& out, const Vec3& v);

Vec3 operator+(const Vec3& lhs, const Vec3& rhs);

Vec3 operator-(const Vec3& lhs, const Vec3& rhs);

Vec3 operator*(const Vec3& lhs, const Vec3& rhs);

Vec3 operator*(double lhs, const Vec3& rhs);

Vec3 operator*(const Vec3& lhs, double rhs);

Vec3 operator/(const Vec3& lhs, double rhs);

double dot(const Vec3& lhs, const Vec3& rhs);

Vec3 cross(const Vec3& lhs, const Vec3& rhs);

Vec3 unitVector(const Vec3& vector);

#endif