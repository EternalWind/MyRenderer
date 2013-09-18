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
	virtual bool Intersect(const Ray& ray, Intersection& intersection, void* additional_data = nullptr) const = 0;

	virtual ~IIntersectTarget() = 0 {}
};