#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"


//Takes color inputs from [0, 1] range.
using Color = Vec3;

void writeColor(std::ostream& out, const Color& pixel_color) {
	auto r = pixel_color.getX();
	auto g = pixel_color.getY();
	auto b = pixel_color.getZ();

	//Translate the [0, 1] component values into [0, 255] range.
	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	//Write out pixel color components.
	out << rbyte << ' ' << gbyte << ' ' << bbyte << std::endl;
}

#endif