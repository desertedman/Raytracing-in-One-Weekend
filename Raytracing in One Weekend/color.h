#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"


//Takes color inputs from [0, 1] range.
using Color = Vec3;

inline double convertLinearToGamma(double linear_component) {
	if (linear_component > 0) {
		return std::sqrt(linear_component);
	}

	return 0;
}

void writeColor(std::ostream& out, const Color& pixel_color) {
	auto r = pixel_color.getX();
	auto g = pixel_color.getY();
	auto b = pixel_color.getZ();

	//Apply a linear to gamma transform for gamma 2
	r = convertLinearToGamma(r);
	g = convertLinearToGamma(g);
	b = convertLinearToGamma(b);

	//Translate the [0, 1] component values into [0, 255] range.
	static const Interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clampToInterval(r));
	int gbyte = int(256 * intensity.clampToInterval(g));
	int bbyte = int(256 * intensity.clampToInterval(b));

	//Write out pixel color components.
	out << rbyte << ' ' << gbyte << ' ' << bbyte << std::endl;
}

#endif