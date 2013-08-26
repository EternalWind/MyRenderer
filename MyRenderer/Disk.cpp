#include "Disk.h"


Disk::Disk(float radius, const Vector3& center, const Vector3& orientation, const ColorRGBA& color) :
	Plane(center, orientation, color),
	m_Radius(radius),
	m_SquareRadius(radius * radius)
{
}

shared_ptr<Intersection> Disk::Intersect(const Ray& ray) const
{
	Range<float> orig_range = ray.EffectRange();
	shared_ptr<Intersection> intersection = Plane::Intersect(ray);

	if (intersection.get() != nullptr)
	{
		Vector3 intersect_point = intersection->Position();
		float distance_sq = (intersect_point - m_Center).SquareLength();

		if (distance_sq <= m_SquareRadius)
			return intersection;
	}

	return nullptr;
}

Disk::~Disk(void)
{
}
