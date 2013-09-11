#include "Triangle.h"


Triangle::Triangle(const Vector3* v0, const Vector3* v1, const Vector3* v2, const ColorRGBA& color, bool is_double_sided) :
	Shape(color),
	m_V0(v0),
	m_V1(v1),
	m_V2(v2),
	m_V0V1(*m_V1 - *m_V0),
	m_V0V2(*m_V2 - *m_V0),
	m_IsDoubleSided(is_double_sided)
{
	Vector3 a = *v1 - *v0;
	Vector3 b = *v2 - *v0;

	m_Normal = a.CrossProduct(b);
	m_NormalSqLength = m_Normal.SquareLength();

	m_D = -(m_Normal.DotProduct(*m_V0));
}

bool Triangle::Intersect(const Ray& ray, Intersection& intersection) const
{
	float t = 0.f;
	ParycentricCoord coord;

#ifdef MOLLER_TRUMBORE

	Vector3 pvec = ray.Direction().CrossProduct(m_V0V2);
	float det = m_V0V1.DotProduct(pvec);

	if (abs(det) < numeric_limits<float>::epsilon())
		return false;

	if (!m_IsDoubleSided && det < 0.f)
		return false;

	Vector3 tvec = ray.Origin() - *m_V0;
	Vector3 qvec = tvec.CrossProduct(m_V0V1);

	if (det > 0.f)
	{
		coord.u = tvec.DotProduct(pvec);

		if (coord.u < 0.f || coord.u > det)
			return false;

		coord.v = ray.Direction().DotProduct(qvec);

		if (coord.v < 0.f || coord.v > det)
			return false;

		coord.w = coord.u + coord.v;

		if (coord.w > det)
			return false;
	}
	else
	{
		coord.u = tvec.DotProduct(pvec);

		if (coord.u > 0.f || coord.u < det)
			return false;

		coord.v = ray.Direction().DotProduct(qvec);

		if (coord.v > 0.f || coord.v < det)
			return false;

		coord.w = coord.u + coord.v;

		if (coord.w < det)
			return false;
	}

	float det_inv = 1 / det;

	coord.u *= det_inv;
	coord.v *= det_inv;
	coord.w = 1 - coord.u - coord.v;

	t = m_V0V2.DotProduct(qvec) * det_inv;

	if (!Math::Contain(t, ray.EffectRange()))
		return false;
#else
	float dir_norm = m_Normal.DotProduct(ray.Direction());

	if (abs(dir_norm) < numeric_limits<float>::epsilon())
		return false;

	if (dir_norm > 0.f && !m_IsDoubleSided)
		return false;

	float orig_norm = m_Normal.DotProduct(ray.Origin());
	t = -(orig_norm + m_D) / dir_norm;

	if (!Math::Contain(t, ray.EffectRange()))
		return false;

	Vector3 p_hit = ray.Origin() + ray.Direction() * t;

	Vector3 v0_v1 = *m_V1 - *m_V0;
	Vector3 v1_v2 = *m_V2 - *m_V1;

	Vector3 v0_p = p_hit - *m_V0;
	Vector3 v1_p = p_hit - *m_V1;

	coord.v = m_Normal.DotProduct(v0_v1.CrossProduct(v0_p)) / m_NormalSqLength;

	if (coord.v < 0.f || coord.v > 1.f)
		return false;

	coord.w = m_Normal.DotProduct(v1_v2.CrossProduct(v1_p)) / m_NormalSqLength;

	if (coord.w < 0.f || coord.w > 1.f)
		return false;

	coord.u = 1.f - coord.v - coord.w;

	if (coord.u < 0.f)
		return false;
#endif

	intersection.SetDistance(t);
	intersection.SetIntersectObject((IIntersectTarget*)this);
	intersection.SetParycentricCoordinate(coord);
	intersection.SetTestObject(&ray);

	return true;
}

Triangle::~Triangle(void)
{
}
