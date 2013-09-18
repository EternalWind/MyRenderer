#include "Sphere.h"
#include "Math.h"
#include "PolygonGenerator.h"

//#define USE_GEOMETRIC

Sphere::Sphere(const Vector3& center, float radius, const ColorRGBA& color) :
	Primitive(color),
	m_Center(center),
	m_Radius(radius)
{
}

bool Sphere::Intersect(const Ray& ray, Intersection& intersection, void* additional_data) const
{
	Range<float> t;

#ifdef USE_GEOMETRIC
	Vector3 l = m_Center - ray.Origin();
	float t_ca = l.DotProduct(ray.Direction());
	float d_sq = l.SquareLength() - t_ca * t_ca;
	float r_sq = m_Radius * m_Radius;

	if (d_sq > r_sq)
	{
		return false;
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
		return false;
#endif

	Range<float> range = ray.EffectRange();

	if (Math::Contain(t.Min, range))
		intersection.SetDistance(t.Min);
	else if (Math::Contain(t.Max, range))
		intersection.SetDistance(t.Max);
	else
		return false;

	intersection.SetIntersectObject((IIntersectTarget*)this);
	intersection.SetTestObject(&ray);

	return true;
}

shared_ptr<Mesh> Sphere::ToMesh(unsigned divs) const
{
	return PolygonGenerator::Sphere(m_Radius, divs, m_Center);
}

Sphere::~Sphere(void)
{
}
