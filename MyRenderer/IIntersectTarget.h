#pragma once

#include <vector>
#include <memory>

#include "Ray.h"
#include "Intersection.h"
#include "ColorRGBA.h"

using namespace std;

class Intersection;

class IIntersectTarget
{
public:
	virtual shared_ptr<Intersection> Intersect(const Ray& ray) const = 0;

	virtual ~IIntersectTarget() = 0 {}
};