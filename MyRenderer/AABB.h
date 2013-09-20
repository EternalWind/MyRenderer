#pragma once

#include "Vector3.h"
#include "IBoundingVolume.h"

class AABB : public IBoundingVolume
{
public:
	AABB(const Vector3& min_extent, const Vector3& max_extent, const ColorRGBA& color = ColorRGBA(1.f, 1.f, 1.f));

	AABB(const AABB& other);

	Vector3 MinExtent() const;

	Vector3 MaxExtent() const;

	void ExtendBy(const IBoundingVolume* other);

	bool Intersect(const Ray& ray, Intersection& intersection, void* additional_data = nullptr) const;

	~AABB(void);

private:
	Vector3 m_MinExtent;
	Vector3 m_MaxExtent;
};

inline Vector3 AABB::MinExtent() const
{
	return m_MinExtent;
}

inline Vector3 AABB::MaxExtent() const
{
	return m_MaxExtent;
}