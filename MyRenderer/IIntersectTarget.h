#pragma once

#include "Ray.h"

class IIntersectTarget
{
public:
	virtual bool Intersect(const Ray& ray) const = 0;
};