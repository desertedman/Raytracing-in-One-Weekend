#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


using namespace std;


int main() {

	//World
	HittableList world;

	world.addObject(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.addObject(make_shared<Sphere>(Point3(0, -100.5, -1), 100));


	Camera cam;
	cam.m_AspectRatio = 16.0 / 9.0;
	cam.m_ImageWidth = 400;
	cam.m_SamplesPerPixel = 100;
	//cam.m_FileName = "someFileName.ppm"


	cam.renderCamera(world);

}