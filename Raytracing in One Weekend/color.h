#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

//Takes color inputs from [0, 1] range.
using Color = Vec3;

void writeColor(std::ostream& out, const Color& pixel_color);

#endif