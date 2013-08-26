#include "Sphere.h"
#include "Math.h"

//#define USE_GEOMETRIC

Sphere::Sphere(const Vector3& center, float radius, const ColorRGBA& color) :
	Shape(color),
	m_Center(center),
	m_Radius(radius)
{
}

shared_ptr<Intersection> Sphere::Intersect(const Ray& ray) const
{
	Range<float> t;

#ifdef USE_GEOMETRIC
	Vector3 l = m_Center - ray.Origin();
	float t_ca = l.DotProduct(ray.Direction());
	float d_sq = l.SquareLength() - t_ca * t_ca;
	float r_sq = m_Radius * m_Radius;

	if (d_sq > r_sq)
	{
		return nullptr;
	}
	else if (d_sq == r_sq)
	{
		t.Min = t.Max = t_ca;
	}
	else
	{
		float t_hc = sqrt(r_sq - d_sq);
		t.Min = t_ca - t_hc;
		t.Max = t_ca + t_hc;
	}
#else
	Vector3 translated_origin = ray.Origin() - m_Center;

	float a = 1.f;
	float b = (ray.Direction() * 2).DotProduct(translated_origin);
	float c = translated_origin.SquareLength() - m_Radius * m_Radius;

	if (!Math::SolveQuadratic(a, b, c, t.Min, t.Max))
		return nullptr;
#endif

	Range<float> range = ray.EffectRange();

	if (Math::Contain(t.Min, range))
	{
		return shared_ptr<Intersection>(new Intersection(ray.Origin() + ray.Direction() * t.Min, this, t.Min));
	}

	if (Math::Contain(t.Max, range))
	{
		return shared_ptr<Intersection>(new Intersection(ray.Origin() + ray.Direction() * t.Max, this, t.Max));
	}

	return nullptr;
}

Sphere::~Sphere(void)
{
}