#include "sphere.h"

Sphere::Sphere(const Point3& center, double radius) {
	(*this).center = center;
	(*this).radius = fmax(0, radius);
}

bool Sphere::hit(const Ray& curr_ray, double ray_tmin, double ray_tmax, HitRecord& rec) const {
	Vec3 raycast = (*this).center - curr_ray.getOrigin();
	double a = curr_ray.getDirection().getLengthSquared();
	double h = dot(curr_ray.getDirection(), raycast);
	auto c = raycast.getLengthSquared() - radius * radius;

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

	rec.setNewParameterT(root);
	rec.m_curr_point = curr_ray.getPosition(rec.getParameterT());
	//rec.setCurrPoint(curr_ray.getPosition(rec.getParameterT()));
	rec.m_normal = (rec.getCurrPoint() - center) / radius;

	return true;
}

