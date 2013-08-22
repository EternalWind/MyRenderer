#include "Disk.h"


Disk::Disk(float radius, const Vector3& center, const Vector3& orientation) :
	Plane(center, orientation),
	m_Radius(radius),
	m_SquareRadius(radius * radius)
{
}

bool Disk::Intersect(Ray& ray, vector<Intersection>& intersections) const
{
	Range<float> orig_range = ray.EffectRange();

	if (Plane::Intersect(ray, intersections))
	{
		Vector3 intersect_point = intersections.back().Position();
		float distance_sq = (intersect_point - m_Center).SquareLength();

		if (distance_sq <= m_SquareRadius)
			return true;

		ray.SetEffectRange(orig_range);
		intersections.pop_back();
	}

	return false;
}

Disk::~Disk(void)
{
}
