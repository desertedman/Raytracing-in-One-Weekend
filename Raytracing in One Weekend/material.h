#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

class HitRecord;

class Material {
public:

	virtual ~Material() = default;

	virtual bool isRayScattered(const Ray& incomingRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const {
		return false;
	}
};


class Lambertian : public Material {
public:
	Lambertian(const Color& albedo) {
		mAlbedo = albedo;
	}

	bool isRayScattered(const Ray& incomingRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {

		// Lambertian diffuse model
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

	bool isRayScattered(const Ray& incomingRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {

		Vec3 reflectedRay = reflectVector(incomingRay.getDirection(), record.normal);
		reflectedRay = getUnitVector(reflectedRay) + (mFuzz * generateRandUnitVector());

		scatteredRay = Ray(record.currPoint, reflectedRay);
		attenuation = mAlbedo;
		return (getDotProduct(scatteredRay.getDirection(), record.normal) > 0);
	}

private:
	Color mAlbedo;
	double mFuzz;
};

class Dielectric : public Material {
public:
	Dielectric(double refractionIndex) {
		mRefractionIndex = refractionIndex;
	}

	bool isRayScattered(const Ray& incomingRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {
		attenuation = Color(1.0, 1.0, 1.0);
		double refractionIndex;

		if (record.isFrontFace)
			refractionIndex = 1.0 / (*this).mRefractionIndex;

		else
			refractionIndex = (*this).mRefractionIndex;

		Vec3 unitDirection = getUnitVector(incomingRay.getDirection());
		double cosTheta = std::fmin(getDotProduct(-unitDirection, record.normal), 1.0);
		double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

		bool cannotRefract = refractionIndex * sinTheta > 1;
		Vec3 direction;

		if (cannotRefract)
			direction = reflectVector(unitDirection, record.normal);

		else
			direction = refractVector(unitDirection, record.normal, refractionIndex);

		scatteredRay = Ray(record.currPoint, direction);
		return true;
	}

private:
	// Refractive index in vacuum or air, or the ratio of the material's refractive index over
	// the refractive index of the enclosing media
	double mRefractionIndex;
};
#endif