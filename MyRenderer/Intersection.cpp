#include "Intersection.h"

Intersection::Intersection(const Vector3& position, const IIntersectTarget* object, float distance, const ParycentricCoord& uvw) :
	m_Position(position),
	m_IntersectObjectHandle(const_cast<IIntersectTarget*>(object)),
	m_Distance(distance),
	m_ParycentricCoord(uvw)
{
}

Intersection::~Intersection(void)
{
}
