#pragma once

#include "Plane.h"

class Disk :
	public Plane
{
public:
	Disk(float radius, const Vector3& center = Vector3(), const Vector3& orientation = Vector3(0.f, 0.f, 1.f), const ColorRGBA& color = ColorRGBA(1.f, 1.f, 1.f));

	float Radius() const;

	shared_ptr<Intersection> Intersect(const Ray& ray) const;

	~Disk(void);

private:
	float m_Radius;
	float m_SquareRadius;
};

// Implementation for inline methods.
inline float Disk::Radius() const
{
	return m_Radius;
}