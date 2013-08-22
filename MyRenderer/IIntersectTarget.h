#pragma once

#include <vector>

#include "Ray.h"
#include "Intersection.h"

using namespace std;

class Intersection;

class IIntersectTarget
{
public:
	virtual bool Intersect(Ray& ray, vector<Intersection>& intersections) const = 0;

	virtual ~IIntersectTarget() = 0 {}
};