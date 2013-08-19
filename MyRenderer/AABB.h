#pragma once

#include "Vector3.h"
#include "IIntersectTarget.h"

class AABB : public IIntersectTarget
{
public:
	AABB(const Vector3& min_extent, const Vector3& max_extent);

	Vector3 MinExtent() const;

	Vector3 MaxExtent() const;

	bool Intersect(const Ray& ray) const;

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