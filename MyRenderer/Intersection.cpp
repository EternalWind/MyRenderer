#include "Intersection.h"

Intersection::Intersection(const Vector3& position, const IIntersectTarget* object, float distance) :
	m_Position(position),
	m_IntersectObjectHandle(const_cast<IIntersectTarget*>(object)),
	m_Distance(distance)
{
}

Intersection::~Intersection(void)
{
}
