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
#ifdef MOLLER_TRUMBORE
	Vector3 v0_v1 = m_V1 - m_V0;
	Vector3 v0_v2 = m_V2 - m_V0;

	Vector3 pvec = ray.Direction().CrossProduct(v0_v2);
	float det = v0_v1.DotProduct(pvec);

	if (abs(det) < numeric_limits<float>::epsilon())
		return nullptr;

	if (!m_IsDoubleSided && det < 0.f)
		return nullptr;

	Vector3 tvec = ray.Origin() - m_V0;
	Vector3 qvec = tvec.CrossProduct(v0_v1);

	ParycentricCoord coord;

	if (det > 0.f)
	{
		coord.u = tvec.DotProduct(pvec);

		if (coord.u < 0.f || coord.u > det)
			return nullptr;

		coord.v = ray.Direction().DotProduct(qvec);

		if (coord.v < 0.f || coord.v > det)
			return nullptr;

		coord.w = coord.u + coord.v;

		if (coord.w > det)
			return nullptr;
	}
	else
	{
		coord.u = tvec.DotProduct(pvec);

		if (coord.u > 0.f || coord.u < det)
			return nullptr;

		coord.v = ray.Direction().DotProduct(qvec);

		if (coord.v > 0.f || coord.v < det)
			return nullptr;

		coord.w = coord.u + coord.v;

		if (coord.w < det)
			return nullptr;
	}

	float det_inv = 1 / det;

	coord.u *= det_inv;
	coord.v *= det_inv;
	coord.w = 1 - coord.u - coord.v;

	float t = v0_v2.DotProduct(qvec);

	if (!Math::Contain(t, ray.EffectRange()))
		return nullptr;

	return shared_ptr<Intersection>(new Intersection(&ray, (IIntersectTarget*)this, t, coord));

#else
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

	Vector3 v0_v1 = m_V1 - m_V0;
	Vector3 v1_v2 = m_V2 - m_V1;

	Vector3 v0_p = p_hit - m_V0;
	Vector3 v1_p = p_hit - m_V1;

	ParycentricCoord coord;

	coord.v = m_Normal.DotProduct(v0_v1.CrossProduct(v0_p)) / m_NormalSqLength;

	if (coord.v < 0.f || coord.v > 1.f)
		return nullptr;

	coord.w = m_Normal.DotProduct(v1_v2.CrossProduct(v1_p)) / m_NormalSqLength;

	if (coord.w < 0.f || coord.w > 1.f)
		return nullptr;

	coord.u = 1.f - coord.v - coord.w;

	if (coord.u < 0.f)
		return nullptr;

	return shared_ptr<Intersection>(new Intersection(&ray, (IIntersectTarget*)this, t, coord));
#endif
}

Triangle::~Triangle(void)
{
}
