#include "Plane.h"


Plane::Plane(const Vector3& center, const Vector3& orientation, const ColorRGBA& color) :
	Shape(color),
	m_Center(center),
	m_Orientation(orientation)
{
	m_Orientation.Normalise();
}

shared_ptr<Intersection> Plane::Intersect(const Ray& ray) const
{
	float dir_norm = ray.Direction().DotProduct(m_Orientation);

	if (abs(dir_norm) < std::numeric_limits<float>::epsilon())
		return nullptr;

	float t = (m_Center - ray.Origin()).DotProduct(m_Orientation) / dir_norm;

	Range<float> range = ray.EffectRange();
	if (Math::Contain(t, range))
	{
		return shared_ptr<Intersection>(new Intersection(&ray, (IIntersectTarget*)this, t));
	}

	return nullptr;
}

Plane::~Plane(void)
{
}
