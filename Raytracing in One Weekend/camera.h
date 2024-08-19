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
		initialize();

		(*this).m_outfs << "P3\n" << (*this).m_image_width << ' ' << (*this).m_image_height << "\n255\n";


		for (int j = 0; j < (*this).m_image_height; j++) {
			std::clog << "\rScanlines remaining: " << ((*this).m_image_height - j) << ' ' << std::flush;

			for (int i = 0; i < (*this).m_image_width; i++) {
				auto pixel_center = (*this).m_pixel00_loc + (i * (*this).m_pixel_delta_u) + (j * (*this).m_pixel_delta_v);
				auto ray_direction = pixel_center - (*this).m_center;
				Ray camera_ray((*this).m_center, ray_direction);

				Color pixel_color = rayColor(camera_ray, world);
				writeColor((*this).m_outfs, pixel_color);
			}
		}


		std::clog << "\r\rDone.                 \n";
	}

public:
	//Public variables

	double m_aspect_ratio = 1.0;	//Ratio of image width over height
	int m_image_width = 100;		//Rendered image width in pixel count


private:
	//Private functions

	void initialize() {

		//Ensure that a valid file can be output.
		(*this).m_outfs.open((*this).m_filename);
		if (!(*this).m_outfs.good()) {
			std::cout << "Error! Cannot write to file!" << std::endl;
			exit(1);
		}


		(*this).m_image_height = int((*this).m_image_width / m_aspect_ratio);

		if ((*this).m_image_height < 1) {
			(*this).m_image_height = 1;
		}

		(*this).m_center = Point3(0, 0, 0);


		//Determine viewport dimensions.
		double focal_length = 1.0;
		double viewport_height = 2.0;
		double viewport_width = viewport_height * (double((*this).m_image_width) / (*this).m_image_height);


		//Calculate the vectors across the horizontal and down the vertical viewport edges.
		Vec3 viewport_u = Vec3(viewport_width, 0, 0);
		Vec3 viewport_v = Vec3(0, -viewport_height, 0);


		//Calculate the horizontal and vertical delta vectors from pixel to pixel.
		(*this).m_pixel_delta_u = viewport_u / (*this).m_image_width;
		(*this).m_pixel_delta_v = viewport_v / (*this).m_image_height;


		//Calculate location of upper left pixel.
		auto viewport_upper_left = (*this).m_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		(*this).m_pixel00_loc = viewport_upper_left + 0.5 * ((*this).m_pixel_delta_u + (*this).m_pixel_delta_v);

	}

	Color rayColor(const Ray& curr_ray, const Hittable& world) const {

		HitRecord record;

		if (world.isObjectHit(curr_ray, Interval(0, infinity), record)) {
			return 0.5 * (record.m_normal + Color(1, 1, 1));
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

	int m_image_height;
	Point3 m_center;
	Point3 m_pixel00_loc;
	Vec3 m_pixel_delta_u;
	Vec3 m_pixel_delta_v;


	//File output
	std::ofstream m_outfs;
	std::string m_filename = "output.ppm";

};


#endif