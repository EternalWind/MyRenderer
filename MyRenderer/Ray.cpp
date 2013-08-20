#include "Ray.h"
#include "Exception.h"

Ray::Ray(const Vector3& origin, const Vector3& direction, const Range<float>& effect_range) :
	m_Origin(origin),
	m_Direction(direction),
	m_InvDirection(1 / direction.X(), 1 / direction.Y(), 1 / direction.Z()),
	m_EffectRange(effect_range)
{
	m_Direction.Normalise();
}

Ray::~Ray(void)
{
}
