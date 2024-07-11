#include "color.h"

using namespace std;

void write_color(std::ostream& out, const color& pixel_color) {
	auto r = pixel_color.getX();
	auto g = pixel_color.getY();
	auto b = pixel_color.getZ();

	//Translate the [0, 1] component values into [0, 255] range.
	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	//Write out pixel color components.
	out << rbyte << ' ' << gbyte << ' ' << bbyte << endl;
}