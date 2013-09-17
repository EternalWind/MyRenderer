#include "Plane.h"


Plane::Plane(const Vector3& center, const Vector3& orientation, const ColorRGBA& color) :
	Primitive(color),
	m_Center(center),
	m_Orientation(orientation)
{
	m_Orientation.Normalise();
}

bool Plane::Intersect(const Ray& ray, Intersection& intersection) const
{
	float dir_norm = ray.Direction().DotProduct(m_Orientation);

	if (abs(dir_norm) < std::numeric_limits<float>::epsilon())
		return false;

	float t = (m_Center - ray.Origin()).DotProduct(m_Orientation) / dir_norm;

	Range<float> range = ray.EffectRange();

	if (Math::Contain(t, range))
	{
		intersection.SetDistance(t);
		intersection.SetIntersectObject((IIntersectTarget*)this);
		intersection.SetTestObject(&ray);

		return true;
	}

	return false;
}

Plane::~Plane(void)
{
}
