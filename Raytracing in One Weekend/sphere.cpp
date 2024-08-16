#include "sphere.h"

Sphere::Sphere(const Point3& center, double radius) {
	(*this).m_center = center;
	(*this).m_radius = fmax(0, radius);
}

bool Sphere::isObjectHit(const Ray& curr_ray, const double ray_tmin, const double ray_tmax, HitRecord& record) const {
	Vec3 raycast = (*this).m_center - curr_ray.getOrigin();
	double a = curr_ray.getDirection().getLengthSquared();
	double h = dot(curr_ray.getDirection(), raycast);
	auto c = raycast.getLengthSquared() - m_radius * m_radius;

	double discriminant = h * h - a * c;
	if (discriminant < 0) {
		return false;
	}

	double sqrt_discriminant = sqrt(discriminant);

	//Find the nearest root that lies in the acceptable range.
	auto root = (h - sqrt_discriminant) / a;

	if (root <= ray_tmin || ray_tmax <= root) {
		root = (h + sqrt_discriminant) / a;

		if (root <= ray_tmin || ray_tmax <= root) {
			return false;
		}
	}

	record.m_parameter_t = root;
	record.m_curr_point = curr_ray.getPosition(record.m_parameter_t);
	Vec3 outward_normal = (record.m_curr_point - (*this).m_center) / (*this).m_radius;
	record.setFaceNormal(curr_ray, outward_normal);
	//record.m_normal = (record.m_curr_point - m_center) / m_radius;

	return true;
}

