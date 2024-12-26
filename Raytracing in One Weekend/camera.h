#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"
#include "material.h"

#include <string>
#include <fstream>


class Camera {
public:
	//Public functions

	void renderCamera(const Hittable& world) {
		initializeCamera();

		outFS << "P3\n" << imageWidth << ' ' << mImageHeight << "\n255\n";


		for (int j = 0; j < mImageHeight; j++) {
			std::clog << "\rScanlines remaining: " << ((*this).mImageHeight - j) << ' ' << std::flush;

			for (int i = 0; i < imageWidth; i++) {

				Color pixelColor(0, 0, 0);

				for (int sample = 0; sample < samplesPerPixel; sample++) {
					Ray cameraRay = getRay(i, j);
					pixelColor += getRayColor(cameraRay, maxDepth, world);
				}


				//pixelColor adds up the total color from some number of samples
				//Then the final pixel color is averaged out over the number of samples
				writeColor(outFS, mPixelSamplesScale * pixelColor);
			}
		}


		std::clog << "\r\rDone.                 \n";
	}

public:
	//Public variables

	double aspectRatio = 1.0;		//Ratio of image width over height
	int imageWidth = 100;			//Rendered image width in pixel count
	int samplesPerPixel = 10;		//Count of random samples for each pixel
	int maxDepth = 10;			//Maximum number of ray bounces into scene


	std::string fileName = "output.ppm";		//Name of file output


private:
	//Private functions

	void initializeCamera() {

		//Ensure that a valid file can be output.
		outFS.open(".\\output\\" + fileName);
		if (!outFS.good()) {
			std::cout << "Error! Cannot write to file!" << std::endl;
			exit(1);
		}


		mImageHeight = int(imageWidth / aspectRatio);

		if (mImageHeight < 1) {
			mImageHeight = 1;
		}

		mPixelSamplesScale = 1.0 / samplesPerPixel;

		(*this).mCenter = Point3(0, 0, 0);


		//Determine viewport dimensions.
		double focalLength = 1.0;
		double viewportHeight = 2.0;
		double viewportWidth = viewportHeight * (double(imageWidth) / mImageHeight);


		//Calculate the vectors across the horizontal and down the vertical viewport edges.
		Vec3 viewportU = Vec3(viewportWidth, 0, 0);
		Vec3 viewportV = Vec3(0, -viewportHeight, 0);


		//Calculate the horizontal and vertical delta vectors from pixel to pixel.
		mPixelDeltaU = viewportU / imageWidth;
		mPixelDeltaV = viewportV / mImageHeight;


		//Calculate location of upper left pixel.
		auto viewport_upper_left = mCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
		mPixel00Loc = viewport_upper_left + 0.5 * (mPixelDeltaU + mPixelDeltaV);

	}

	Ray getRay(int i, int j) const {
		//Construct a camera ray originating from the origin and directed at randomly sampled 
		// point around the pixel location i, j.

		Vec3 offset = sampleSquare();
		auto pixel_sample = mPixel00Loc + ((i + offset.getX()) * mPixelDeltaU) + ((j + offset.getY()) * mPixelDeltaV);

		auto rayOrigin = mCenter;
		auto rayDirection = pixel_sample - rayOrigin;

		return Ray(rayOrigin, rayDirection);
	}

	Vec3 sampleSquare() const {
		//Returns the vector to a random point in the [-.5, -.5] - [+.5, +.5] unit square.
		return Vec3(getRandomDouble() - 0.5, getRandomDouble() - 0.5, 0);
	}

	Color getRayColor(const Ray& curr_ray, int depth, const Hittable& world) const {

		//If we've exceeded the ray bounce limit, no more light is gathered;
		if (depth <= 0) {
			return Color(0, 0, 0);
		}

		HitRecord record;


		if (world.isObjectHit(curr_ray, Interval(0.001, infinity), record)) {
			Ray scattered_ray;
			Color attenuation;

			if (record.currMaterial->isRayScattered(curr_ray, record, attenuation, scattered_ray)) {
				return attenuation * getRayColor(scattered_ray, depth - 1, world);
			}

			return Color(0, 0, 0);

			//Recursively determine the color of ray by generating new rays at the point of intersection
			//Fire off rays until max ray bounce depth, or until we hit nothing
		}


		//Background Color
		Vec3 unit_direction = getUnitVector(curr_ray.getDirection());
		//Shift normalized Y coordinate from [-1, 1] to [0, 1] range
		auto a = 0.5 * (unit_direction.getY() + 1.0);
		//Return linear blended color of background
		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	}


private:
	//Private variables

	int mImageHeight;
	Point3 mCenter;
	Point3 mPixel00Loc;
	Vec3 mPixelDeltaU;
	Vec3 mPixelDeltaV;
	double mPixelSamplesScale;		//Color scale factor for a sum of pixel samples


	//File output
	std::ofstream outFS;

};


#endif