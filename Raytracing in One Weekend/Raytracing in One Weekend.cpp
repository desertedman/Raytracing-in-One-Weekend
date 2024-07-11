#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"

using namespace std;

int main() {

	//Image

	//ifstream inFS;
	ofstream outFS;
	string fileName = "output.ppm";

	int image_width = 256;
	int image_height = 256;

	//Check if file already exists; not implemented
	//inFS.open(fileName);

	//File Output
	
	outFS.open(fileName);
	if (!outFS.good()) {
		cout << "Error! File could not be written";
		exit;
	}

	//Render

	cout << "Rendering..." << endl;

	outFS << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++) {

		clog << "\rScanlines remaining: " << image_height - j << ' ' << flush;		//what does flush do?

		for (int i = 0; i < image_width; i++) {

			//pixels are indexed from [0, 255], so we subtract 1 from width/height

			/*
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			outFS << ir << ' ' << ig << ' ' << ib << endl;
			*/

			auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);

			write_color(outFS, pixel_color);
		}

	}

	outFS.close();

	clog << "\r...Complete!                 " << endl;

	return 0;
} 