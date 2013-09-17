#pragma once

#include "Vector3.h"
#include "Primitive.h"

class AABB : public Primitive
{
public:
	AABB(const Vector3& min_extent, const Vector3& max_extent, const ColorRGBA& color = ColorRGBA(1.f, 1.f, 1.f));

	AABB(const AABB& other);

	Vector3 MinExtent() const;

	Vector3 MaxExtent() const;

	bool Intersect(const Ray& ray, Intersection& intersection) const;

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