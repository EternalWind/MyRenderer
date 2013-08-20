#pragma once

#include "IIntersectTarget.h"
#include "Vector3.h"

class Sphere : public IIntersectTarget
{
public:
	Sphere(const Vector3& center, float radius);

	bool Intersect(Ray& ray) const; 

	~Sphere(void);

private:
	Vector3 m_Center;
	float m_Radius;
};

