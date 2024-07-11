#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

//Takes color inputs from [0, 1] range.
using color = vec3;

void write_color(std::ostream& out, const color& pixel_color);

#endif