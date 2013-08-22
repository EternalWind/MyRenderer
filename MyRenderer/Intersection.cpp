#include "Intersection.h"

Intersection::Intersection(const Vector3& position, const IIntersectTarget* object) :
	m_Position(position),
	m_IntersectObjectHandle(const_cast<IIntersectTarget*>(object))
{
}

Intersection::~Intersection(void)
{
}
