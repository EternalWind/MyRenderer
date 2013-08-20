#pragma once

#include "Ray.h"

class IIntersectTarget
{
public:
	virtual bool Intersect(Ray& ray) const = 0;
};