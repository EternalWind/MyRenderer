#pragma once

#include "Defs.h"
#include "Mesh.h"

class PolygonGenerator
{
	MAKE_STATIC(PolygonGenerator)

public:
	static shared_ptr<Mesh> Sphere(float radius, unsigned divs, const Vector3& position = Vector3());
};

