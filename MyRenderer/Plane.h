#pragma once

#include "Shape.h"
#include "Vector3.h"

class Plane :
	public Shape
{
public:
	Plane(const Vector3& center = Vector3(), const Vector3& orientation = Vector3(0.f, 0.f, 1.f), const ColorRGBA& color = ColorRGBA(1.f, 1.f, 1.f));

	Vector3 Center() const;

	Vector3 Orientation() const;

	virtual shared_ptr<Intersection> Intersect(const Ray& ray) const;

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