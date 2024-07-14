#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

using namespace std;


double hitSphere(const Point3& center, double radius, const Ray& current_ray) {
	Vec3 raycast = center - current_ray.getOrigin();
	/*double a = dot(current_ray.getDirection(), current_ray.getDirection());
	double b = dot(-2 * current_ray.getDirection(), raycast);
	double c = dot(raycast, raycast) - radius * radius;
	double discriminant = b * b - 4 * a * c;*/

	double a = current_ray.getDirection().getLengthSquared();
	double h = dot(current_ray.getDirection(), raycast);
	double c = raycast.getLengthSquared() - radius * radius;
	double discriminant = h*h - a * c;

	if (discriminant < 0) {
		return -1.0;
	}

	else {
		//return (-b - sqrt(discriminant)) / (2.0 * a);
		return (h - sqrt(discriminant)) / a;
	}
}


Color rayColor(const Ray& camera_ray) {

	//P(t) = Q + tD
	//t is not exactly the point of intersection, but it is useful for intuition purposes
	double t = hitSphere(Point3(0, 0, -1), 0.5, camera_ray);
	if (t > 0.0) {
		//Normal vector = unit vector of (Point of intersection - center of sphere)
		Vec3 normal = unitVector(camera_ray.getPosition(t) - Vec3(0, 0, -1));
		return 0.5 * Color(normal.getX() + 1, normal.getY() + 1, normal.getZ() + 1);
	}

	Vec3 unit_direction = unitVector(camera_ray.getDirection());
	double a = 0.5 * (unit_direction.getY() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}


int main() {

	//ifstream inFS;
	ofstream out_fs;
	string file_name = "output.ppm";

	//Image
	//400 x 225 
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;


	//Calculate image height; ensure it is at least 1
	int image_height = int(image_width / aspect_ratio);
	if (image_height < 1) {
		image_height = 1;
	}


	//Camera
	//3.5 x 2
	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * (double(image_width) / image_height);
	Point3 camera_center = Point3(0, 0, 0);


	//Calculate the vectors across the horizontal and down the vertical viewport edges.
	Vec3 viewport_horizontal = Vec3(viewport_width, 0, 0);
	Vec3 viewport_vertical = Vec3(0, -viewport_height, 0);


	//Calculate the horizontal and vertical delta vectors from pixel to pixel.
	Vec3 pixel_delta_horizontal = viewport_horizontal / image_width;
	Vec3 pixel_delta_vertical = viewport_vertical / image_height;


	//Calculate the location of the upper left pixel.
	Vec3 viewport_upper_left = camera_center
		- Vec3(0, 0, focal_length) - viewport_horizontal / 2 - viewport_vertical / 2;
	Vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_horizontal + pixel_delta_vertical);


	//Check if file already exists; not implemented
	//inFS.open(file_name);

	//File Output

	out_fs.open(file_name);
	if (!out_fs.good()) {
		cout << "Error! File could not be written";
		exit(1);
	}


	//Render

	cout << "Rendering..." << endl;

	out_fs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

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

			out_fs << ir << ' ' << ig << ' ' << ib << endl;
			*/

			Vec3 pixel_center = pixel00_loc + (i * pixel_delta_horizontal) + (j * pixel_delta_vertical);
			Vec3 ray_direction = pixel_center - camera_center;
			Ray camera_ray(camera_center, ray_direction);

			Color pixel_color = rayColor(camera_ray);
			writeColor(out_fs, pixel_color);
		}

	}

	out_fs.close();
	clog << "\r...Complete!                 " << endl;
	return 0;
}