#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"


class HitRecord;

class Material {
public:

	virtual ~Material() = default;

	virtual bool isRayScattered() const {

	}
};

#endif