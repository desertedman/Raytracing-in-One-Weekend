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
		m_Albedo = albedo;
	}

	bool isRayScattered(const Ray& curr_ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {

		auto scatter_direction = record.m_Normal + generateRandUnitVector();


		//Catch degenerate scatter direction
		if (scatter_direction.isNearZero()) {
			scatter_direction = record.m_Normal;
		}


		scatteredRay = Ray(record.m_CurrPoint, scatter_direction);
		attenuation = m_Albedo;
		return true;
	}

private:
	Color m_Albedo;
};


class Metal : public Material {
public:
	Metal(const Color& albedo) {
		m_Albedo = albedo;
	}

	bool isRayScattered(const Ray& curr_ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {

		Vec3 reflected_ray = reflectVector(curr_ray.getDirection(), record.m_Normal);

		scatteredRay = Ray(record.m_CurrPoint, reflected_ray);
		attenuation = m_Albedo;
		return true;
	}

private:
	Color m_Albedo;
};
#endif