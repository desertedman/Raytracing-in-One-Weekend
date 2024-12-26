#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"


//Takes color inputs from [0, 1] range.
using Color = Vec3;

inline double convertLinearToGamma(double linearComponent) {
	if (linearComponent > 0) {
		return std::sqrt(linearComponent);
	}

	return 0;
}

void writeColor(std::ostream& out, const Color& pixelColor) {
	auto r = pixelColor.getX();
	auto g = pixelColor.getY();
	auto b = pixelColor.getZ();

	//Apply a linear to gamma transform for gamma 2
	r = convertLinearToGamma(r);
	g = convertLinearToGamma(g);
	b = convertLinearToGamma(b);

	//Translate the [0, 1] component values into [0, 255] range.
	static const Interval intensity(0.000, 0.999);
	int rByte = int(256 * intensity.clampToInterval(r));
	int gByte = int(256 * intensity.clampToInterval(g));
	int bByte = int(256 * intensity.clampToInterval(b));

	//Write out pixel color components.
	out << rByte << ' ' << gByte << ' ' << bByte << std::endl;
}

#endif