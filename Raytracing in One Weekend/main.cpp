#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


using namespace std;


Color rayColor(const Ray& camera_ray, const Hittable& world) {

	HitRecord record;
	if (world.isObjectHit(camera_ray, Interval(0, infinity), record)) {
		return 0.5 * (record.m_normal + Color(1, 1, 1));
	}

	Vec3 unit_direction = unitVector(camera_ray.getDirection());
	double a = 0.5 * (unit_direction.getY() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}


int main() {

	//World
	HittableList world;

	world.addObject(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.addObject(make_shared<Sphere>(Point3(0, -100.5, -1), 100));


	Camera cam;
	cam.m_aspect_ratio = 16.0 / 9.0;
	cam.m_image_width = 400;
	cam.m_filename = "testoutput.ppm";

	cam.renderCamera(world);

}