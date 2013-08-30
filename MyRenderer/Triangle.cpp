#include "Triangle.h"


Triangle::Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const ColorRGBA& color, bool is_double_sided) :
	Shape(color),
	m_V0(v0),
	m_V1(v1),
	m_V2(v2),
	m_IsDoubleSided(is_double_sided)
{
	Vector3 a = v1 - v0;
	Vector3 b = v2 - v0;

	m_Normal = a.CrossProduct(b);
	m_NormalSqLength = m_Normal.SquareLength();

	m_D = -(m_Normal.DotProduct(m_V0));
}

shared_ptr<Intersection> Triangle::Intersect(const Ray& ray) const
{
	float dir_norm = m_Normal.DotProduct(ray.Direction());

	if (abs(dir_norm) < numeric_limits<float>::epsilon())
		return nullptr;

	if (dir_norm > 0.f && !m_IsDoubleSided)
		return nullptr;

	float orig_norm = m_Normal.DotProduct(ray.Origin());
	float t = -(orig_norm + m_D) / dir_norm;

	if (!Math::Contain(t, ray.EffectRange()))
		return nullptr;

	Vector3 p_hit = ray.Origin() + ray.Direction() * t;

	Vector3 v1_v0 = m_V1 - m_V0;
	Vector3 v2_v1 = m_V2 - m_V1;

	Vector3 p_v0 = p_hit - m_V0;
	Vector3 p_v1 = p_hit - m_V1;

	ParycentricCoord coord;

	coord.v = m_Normal.DotProduct(v1_v0.CrossProduct(p_v0)) / m_NormalSqLength;

	if (coord.v < 0.f || coord.v > 1.f)
		return nullptr;

	coord.w = m_Normal.DotProduct(v2_v1.CrossProduct(p_v1)) / m_NormalSqLength;

	if (coord.w < 0.f || coord.w > 1.f)
		return nullptr;

	coord.u = 1.f - coord.v - coord.w;

	if (coord.u < 0.f)
		return nullptr;

	return shared_ptr<Intersection>(new Intersection(p_hit, this, t, coord));
}

Triangle::~Triangle(void)
{
}
