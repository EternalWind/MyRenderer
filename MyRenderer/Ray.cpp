#include "Ray.h"
#include "Exception.h"

Ray::Ray(const Vector3& origin, const Vector3& direction, float max_length, float min_length) :
	m_Origin(origin),
	m_Direction(direction),
	m_InvDirection(1 / direction.X(), 1 / direction.Y(), 1 / direction.Z()),
	m_MaxLength(max_length),
	m_MinLength(min_length)
{
	if (m_MaxLength < m_MinLength)
		throw Exception("A minimal value greater than the maximal value is given.");
}

Ray::~Ray(void)
{
}
