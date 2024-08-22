#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"

#include <string>
#include <fstream>


class Camera {
public:
	//Public functions

	void renderCamera(const Hittable& world) {
		initializeCamera();

		m_OutFS << "P3\n" << m_ImageWidth << ' ' << m_ImageHeight << "\n255\n";


		for (int j = 0; j < m_ImageHeight; j++) {
			std::clog << "\rScanlines remaining: " << ((*this).m_ImageHeight - j) << ' ' << std::flush;

			for (int i = 0; i < m_ImageWidth; i++) {

				Color pixel_color(0, 0, 0);

				for (int sample = 0; sample < m_SamplesPerPixel; sample++) {
					Ray camera_ray = getRay(i, j);
					pixel_color += getRayColor(camera_ray, world);
				}

				//pixel_color adds up the total color from some number of samples
				//Then the final pixel color is multiplied by 1/num_of_samples,
				//which is the average of the final color
				writeColor(m_OutFS, m_PixelSamplesScale * pixel_color);
			}
		}


		std::clog << "\r\rDone.                 \n";
	}

public:
	//Public variables

	double m_AspectRatio = 1.0;	//Ratio of image width over height
	int m_ImageWidth = 100;		//Rendered image width in pixel count
	int m_SamplesPerPixel = 10;	//Count of random samples for each pixel

	std::string m_FileName = "output.ppm";		//Name of file output


private:
	//Private functions

	void initializeCamera() {

		//Ensure that a valid file can be output.
		m_OutFS.open(m_FileName);
		if (!m_OutFS.good()) {
			std::cout << "Error! Cannot write to file!" << std::endl;
			exit(1);
		}


		m_ImageHeight = int(m_ImageWidth / m_AspectRatio);

		if (m_ImageHeight < 1) {
			m_ImageHeight = 1;
		}

		m_PixelSamplesScale = 1.0 / m_SamplesPerPixel;

		(*this).m_Center = Point3(0, 0, 0);


		//Determine viewport dimensions.
		double focal_length = 1.0;
		double viewport_height = 2.0;
		double viewport_width = viewport_height * (double(m_ImageWidth) / m_ImageHeight);


		//Calculate the vectors across the horizontal and down the vertical viewport edges.
		Vec3 viewport_u = Vec3(viewport_width, 0, 0);
		Vec3 viewport_v = Vec3(0, -viewport_height, 0);


		//Calculate the horizontal and vertical delta vectors from pixel to pixel.
		m_PixelDeltaU = viewport_u / m_ImageWidth;
		m_PixelDeltaV = viewport_v / m_ImageHeight;


		//Calculate location of upper left pixel.
		auto viewport_upper_left = m_Center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		m_Pixel00Loc = viewport_upper_left + 0.5 * (m_PixelDeltaU + m_PixelDeltaV);

	}

	Ray getRay(int i, int j) const {
		//Construct a camera ray originating from the origin and directed at randomly sampled 
		// point around the pixel location i, j.

		Vec3 offset = sampleSquare();
		auto pixel_sample = m_Pixel00Loc + ((i + offset.getX()) * m_PixelDeltaU) + ((j + offset.getY()) * m_PixelDeltaV);

		auto ray_origin = m_Center;
		auto ray_direction = pixel_sample - ray_origin;

		return Ray(ray_origin, ray_direction);
	}

	Vec3 sampleSquare() const {
		//Returns the vector to a random point in the [-.5, -.5] - [+.5, +.5] unit square.
		return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}

	Color getRayColor(const Ray& curr_ray, const Hittable& world) const {

		HitRecord record;

		if (world.isObjectHit(curr_ray, Interval(0, infinity), record)) {
			return 0.5 * (record.m_Normal + Color(1, 1, 1));
		}


		//Background Color
		Vec3 unit_direction = unitVector(curr_ray.getDirection());
		//Shift normalized Y coordinate from [-1, 1] to [0, 1] range
		auto a = 0.5 * (unit_direction.getY() + 1.0);
		//Return linear blended color of background
		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	}


private:
	//Private variables

	int m_ImageHeight;
	Point3 m_Center;
	Point3 m_Pixel00Loc;
	Vec3 m_PixelDeltaU;
	Vec3 m_PixelDeltaV;
	double m_PixelSamplesScale;		//Color scale factor for a sum of pixel samples


	//File output
	std::ofstream m_OutFS;

};


#endif