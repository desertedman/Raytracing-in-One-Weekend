#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"

using namespace std;

int main() {

	//Image

	ifstream inFS;
	ofstream outFS;
	string fileName = "output.ppm";

	int image_width = 256;
	int image_height = 256;

	inFS.open(fileName);

	outFS.open(fileName);
	if (!outFS.good()) {
		cout << "Error! File could not be output";
		exit;
	}

	//Render

	cout << "Rendering..." << endl;

	outFS << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++) {

		clog << "\rScanlines remaining: " << image_height - j << ' ' << flush;

		for (int i = 0; i < image_width; i++) {

			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			outFS << ir << ' ' << ig << ' ' << ib << endl;
		}

	}

	outFS.close();

	clog << "\r...Complete!                 " << endl;

	return 0;
} 