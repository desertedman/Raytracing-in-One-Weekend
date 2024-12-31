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

    auto groundMaterial = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.addObject(make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto chooseMat = getRandomDouble();
            Point3 center(a + 0.9 * getRandomDouble(), 0.2, b + 0.9 * getRandomDouble());

            if ((center - Point3(4, 0.2, 0)).getLength() > 0.9) {
                shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8) {
                    // diffuse
                    auto albedo = Color::getRandomVector() * Color::getRandomVector();
                    sphereMaterial = make_shared<Lambertian>(albedo);
                    world.addObject(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else if (chooseMat < 0.95) {
                    // metal
                    auto albedo = Color::getRandomVector(0.5, 1);
                    auto fuzz = getRandomDouble(0, 0.5);
                    sphereMaterial = make_shared<Metal>(albedo, fuzz);
                    world.addObject(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else {
                    // glass
                    sphereMaterial = make_shared<Dielectric>(1.5);
                    world.addObject(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.addObject(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.addObject(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.addObject(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

	Camera cam;
	cam.aspectRatio = 16.0 / 9.0;
	cam.imageWidth = 1200;
	cam.samplesPerPixel = 50;
	cam.maxDepth = 10;

	cam.verticalFOV = 20;
	cam.lookFrom = Point3(13, 2, 3);
	cam.lookAt = Point3(0, 0, 0);
	cam.viewUp = Vec3(0, 1, 0);

	cam.defocusAngle = 0.6;
	cam.focusDist = 10.0;

	//cam.fileName = "someFileName.ppm"


	cam.renderCamera(world);

}