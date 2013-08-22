#pragma once

#include "IIntersectTarget.h"
#include "Vector3.h"

class Plane :
	public IIntersectTarget
{
public:
	Plane(const Vector3& center = Vector3(), const Vector3& orientation = Vector3(0.f, 0.f, 1.f));

	Vector3 Center() const;

	Vector3 Orientation() const;

	virtual bool Intersect(Ray& ray, vector<Intersection>& intersections) const;

	virtual ~Plane(void);

protected:
	Vector3 m_Center;
	Vector3 m_Orientation;
};

// Implementation for inline methods.
inline Vector3 Plane::Center() const
{
	return m_Center;
}

inline Vector3 Plane::Orientation() const
{
	return m_Orientation;
}