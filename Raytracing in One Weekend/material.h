#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

class HitRecord;

class Material {
public:

	virtual ~Material() = default;

	virtual bool isRayScattered(const Ray& curr_ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const {
		return false;
	}
};


class Lambertian : public Material {
public:
	Lambertian(const Color& albedo) {
		mAlbedo = albedo;
	}

	bool isRayScattered(const Ray& curr_ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {

		auto scatter_direction = record.normal + generateRandUnitVector();


		//Catch degenerate scatter direction
		if (scatter_direction.isNearZero()) {
			scatter_direction = record.normal;
		}


		scatteredRay = Ray(record.currPoint, scatter_direction);
		attenuation = mAlbedo;
		return true;
	}

private:
	Color mAlbedo;
};


class Metal : public Material {
public:
	Metal(const Color& albedo) {
		mAlbedo = albedo;
	}

	bool isRayScattered(const Ray& curr_ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {

		Vec3 reflected_ray = reflectVector(curr_ray.getDirection(), record.normal);

		scatteredRay = Ray(record.currPoint, reflected_ray);
		attenuation = mAlbedo;
		return true;
	}

private:
	Color mAlbedo;
};
#endif