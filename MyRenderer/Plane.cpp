#include "Plane.h"


Plane::Plane(const Vector3& center, const Vector3& orientation) :
	m_Center(center),
	m_Orientation(orientation)
{
	m_Orientation.Normalise();
}

bool Plane::Intersect(Ray& ray, vector<Intersection>& intersections) const
{
	float dir_norm = ray.Direction().DotProduct(m_Orientation);

	if (abs(dir_norm) < std::numeric_limits<float>::epsilon())
		return false;

	float t = (m_Center - ray.Origin()).DotProduct(m_Orientation) / dir_norm;

	Range<float> range = ray.EffectRange();
	if (Math::Contain(t, range))
	{
		range.Max = t;
		ray.SetEffectRange(range);
		intersections.push_back(Intersection(ray.Origin() + ray.Direction() * t, this));

		return true;
	}

	return false;
}

Plane::~Plane(void)
{
}
