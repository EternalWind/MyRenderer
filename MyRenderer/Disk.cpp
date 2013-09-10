#include "Disk.h"


Disk::Disk(float radius, const Vector3& center, const Vector3& orientation, const ColorRGBA& color) :
	Plane(center, orientation, color),
	m_Radius(radius),
	m_SquareRadius(radius * radius)
{
}

bool Disk::Intersect(const Ray& ray, Intersection& intersection) const
{
	Range<float> orig_range = ray.EffectRange();
	bool flag = Plane::Intersect(ray, intersection);

	if (flag)
	{
		Vector3 intersect_point = ray.Origin() + ray.Direction() * intersection.Distance();
		float distance_sq = (intersect_point - m_Center).SquareLength();

		if (distance_sq > m_SquareRadius)
			flag = false;
	}

	return flag;
}

Disk::~Disk(void)
{
}
