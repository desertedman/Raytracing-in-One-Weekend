#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

class HitRecord;

class Material {
public:

	virtual ~Material() = default;

	virtual bool isRayScattered(const Ray& currRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const {
		return false;
	}
};


class Lambertian : public Material {
public:
	Lambertian(const Color& albedo) {
		mAlbedo = albedo;
	}

	bool isRayScattered(const Ray& currRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {

		auto scatterDirection = record.normal + generateRandUnitVector();


		//Catch degenerate scatter direction
		if (scatterDirection.isNearZero()) {
			scatterDirection = record.normal;
		}

		// We choose to always scatter our ray, so this function will always return true
		scatteredRay = Ray(record.currPoint, scatterDirection);
		attenuation = mAlbedo;
		return true;
	}

private:
	Color mAlbedo;
};


class Metal : public Material {
public:
	Metal(const Color& albedo, double fuzz) {
		mAlbedo = albedo;
		if (fuzz < 1)
			mFuzz = fuzz;

		else
			mFuzz = 1;
	}

	bool isRayScattered(const Ray& currRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {

		Vec3 reflectedRay = reflectVector(currRay.getDirection(), record.normal);
		reflectedRay = getUnitVector(reflectedRay) + (mFuzz * generateRandUnitVector());

		scatteredRay = Ray(record.currPoint, reflectedRay);
		attenuation = mAlbedo;
		return (getDotProduct(scatteredRay.getDirection(), record.normal) > 0);
	}

private:
	Color mAlbedo;
	double mFuzz;
};
#endif