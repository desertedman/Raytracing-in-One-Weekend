#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


//C++ Std Usings

using std::make_shared;
using std::shared_ptr;


//Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


//Utility Functions

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline double getRandomDouble() {
	//Returns a random real in [0,1).
	//Add 1.0 to RAND_MAX so that the denominator is always bigger than numerator.
	return std::rand() / (RAND_MAX + 1.0);
}

inline double getRandomDouble(double min, double max) {
	//Returns a random real in [min, max).
	return min + (max - min) * getRandomDouble();
}


//Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif