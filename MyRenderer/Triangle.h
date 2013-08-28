#pragma once

#include "Shape.h"

class Triangle :
	public Shape
{
public:
	Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const ColorRGBA& color = ColorRGBA(1.f, 1.f, 1.f));

	shared_ptr<Intersection> Intersect(const Ray& ray) const;

	~Triangle(void);

private:
	Vector3 m_V0;
	Vector3 m_V1;
	Vector3 m_V2;
	Vector3 m_Normal;
	
	float m_D;
};

