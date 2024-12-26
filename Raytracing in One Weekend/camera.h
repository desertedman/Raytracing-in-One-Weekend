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

				Color pixel_color(0, 0, 0);

				for (int sample = 0; sample < samplesPerPixel; sample++) {
					Ray camera_ray = getRay(i, j);
					pixel_color += getRayColor(camera_ray, maxDepth, world);
				}


				//pixel_color adds up the total color from some number of samples
				//Then the final pixel color is averaged out over the number of samples
				writeColor(outFS, mPixelSamplesScale * pixel_color);
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
		double focal_length = 1.0;
		double viewport_height = 2.0;
		double viewport_width = viewport_height * (double(imageWidth) / mImageHeight);


		//Calculate the vectors across the horizontal and down the vertical viewport edges.
		Vec3 viewport_u = Vec3(viewport_width, 0, 0);
		Vec3 viewport_v = Vec3(0, -viewport_height, 0);


		//Calculate the horizontal and vertical delta vectors from pixel to pixel.
		mPixelDeltaU = viewport_u / imageWidth;
		mPixelDeltaV = viewport_v / mImageHeight;


		//Calculate location of upper left pixel.
		auto viewport_upper_left = mCenter - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		m_Pixel00Loc = viewport_upper_left + 0.5 * (mPixelDeltaU + mPixelDeltaV);

	}

	Ray getRay(int i, int j) const {
		//Construct a camera ray originating from the origin and directed at randomly sampled 
		// point around the pixel location i, j.

		Vec3 offset = sampleSquare();
		auto pixel_sample = m_Pixel00Loc + ((i + offset.getX()) * mPixelDeltaU) + ((j + offset.getY()) * mPixelDeltaV);

		auto ray_origin = mCenter;
		auto ray_direction = pixel_sample - ray_origin;

		return Ray(ray_origin, ray_direction);
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
	Point3 m_Pixel00Loc;
	Vec3 mPixelDeltaU;
	Vec3 mPixelDeltaV;
	double mPixelSamplesScale;		//Color scale factor for a sum of pixel samples


	//File output
	std::ofstream outFS;

};


#endif