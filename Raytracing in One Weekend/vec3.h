#ifndef VEC3_H
#define VEC3_H

#include <iostream>


class vec3 {
public:
	double xyz[3];

	vec3();
	vec3(double x, double y, double z);

	double getX() const;
	double getY() const;
	double getZ() const;

	vec3 operator-() const;		//not sure what this function is; maybe to negate the vector?
	double operator[](int i) const;
	//double& operator[](int i) const;	i dont fucking know why my implementation doesnt work
	//double operator[](int i) const { return xyz[i]; }
	double& operator[](int i) { return xyz[i]; }

	vec3& operator+=(const vec3& rhs);
	vec3& operator*=(double t);
	vec3& operator/=(double t);

	double getLength() const;
	double getLengthSquared() const;
};


using point3 = vec3;


//Vector Utility Functions

std::ostream& operator<<(std::ostream& out, const vec3& v);

vec3 operator+(const vec3& lhs, const vec3& rhs);

vec3 operator-(const vec3& lhs, const vec3& rhs);

vec3 operator*(const vec3& lhs, const vec3& rhs);

vec3 operator*(double lhs, const vec3& rhs);

vec3 operator*(const vec3& lhs, double rhs);

vec3 operator/(const vec3& lhs, double rhs);

double dot(const vec3& lhs, const vec3& rhs);

vec3 cross(const vec3& lhs, const vec3& rhs);

vec3 unit_vector(const vec3& vector);

#endif