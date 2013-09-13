#pragma once

#include "Vector3.h"

class ICurve
{
public:
	virtual Vector3 PointAt(float t) const = 0;

	virtual ~ICurve() = 0 {}
};