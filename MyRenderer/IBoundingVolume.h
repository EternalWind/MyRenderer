#pragma once

#include "IIntersectTarget.h"

class IBoundingVolume : public IIntersectTarget
{
public:
	virtual void ExtendBy(const IBoundingVolume* other) = 0;

	virtual Vector3 MinExtent() const = 0;

	virtual Vector3 MaxExtent() const = 0;

	virtual ~IBoundingVolume() = 0 {}
};