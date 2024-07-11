#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

using namespace std;


color ray_color(const ray& r) {
	vec3 unit_direction = unit_vector(r.getDirection());
	auto a = 0.5 * (unit_direction.getY() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}


int main() {

	//ifstream inFS;
	ofstream outFS;
	string fileName = "output.ppm";

	//Image

	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;


	//Calculate image height; ensure it is at least 1
	int image_height = int(image_width / aspect_ratio);
	if (image_height < 1) {
		image_height = 1;
	}


	//Camera
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width) / image_height);
	auto camera_center = point3(0, 0, 0);


	//Calculate the vectors across the horizontal and down the vertical viewport edges.
	auto viewport_horizontal = vec3(viewport_width, 0, 0);
	auto viewport_vertical = vec3(0, -viewport_height, 0);


	//Calculate the horizontal and vertical delta vectors from pixel to pixel.
	auto pixel_delta_horizontal = viewport_horizontal / image_width;
	auto pixel_delta_vertical = viewport_vertical / image_height;


	//Calculate the location of the upper left pixel.
	auto viewport_upper_left = camera_center
		- vec3(0, 0, focal_length) - viewport_horizontal / 2 - viewport_vertical / 2;
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_horizontal + pixel_delta_vertical);


	//Check if file already exists; not implemented
	//inFS.open(fileName);

	//File Output

	outFS.open(fileName);
	if (!outFS.good()) {
		cout << "Error! File could not be written";
		exit(1);
	}


	//Render

	cout << "Rendering..." << endl;

	outFS << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++) {

		clog << "\rScanlines remaining: " << image_height - j << ' ' << flush;		//what does flush do?

		for (int i = 0; i < image_width; i++) {

			/*
			//pixels are indexed from [0, 255], so we subtract 1 from width/height
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			outFS << ir << ' ' << ig << ' ' << ib << endl;
			*/

			auto pixel_center = pixel00_loc + (i * pixel_delta_horizontal) + (j * pixel_delta_vertical);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			auto pixel_color = ray_color(r);
			write_color(outFS, pixel_color);
		}

	}

	outFS.close();
	clog << "\r...Complete!                 " << endl;
	return 0;
}