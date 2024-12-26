#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "triangle.h"


using namespace std;


int main() {

	//World
	HittableList world;

	auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto material_left = make_shared<Metal>(Color(0.8, 0.8, 0.8));
	auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2));

	world.addObject(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.addObject(make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
	world.addObject(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.addObject(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));


	Camera cam;
	cam.aspectRatio = 16.0 / 9.0;
	cam.imageWidth = 400;
	cam.samplesPerPixel = 100;
	cam.maxDepth = 50;
	//cam.fileName = "someFileName.ppm"


	cam.renderCamera(world);

}