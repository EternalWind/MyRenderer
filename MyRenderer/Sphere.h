#pragma once

#include "Shape.h"
#include "Vector3.h"
#include "Mesh.h"

class Sphere : public Shape
{
public:
	Sphere(const Vector3& center, float radius, const ColorRGBA& color = ColorRGBA(1.f, 1.f, 1.f));

	bool Intersect(const Ray& ray, Intersection& intersection) const; 

	shared_ptr<Mesh> ToMesh(unsigned divs) const;

	~Sphere(void);

private:
	Vector3 m_Center;
	float m_Radius;
};