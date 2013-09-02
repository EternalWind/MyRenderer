#include "Intersection.h"

Intersection::Intersection(const Ray* test_object, IIntersectTarget* intersect_object, float distance, const ParycentricCoord& uvw) :
	m_TestObjectHandle(test_object),
	m_IntersectObjectHandle(intersect_object),
	m_Distance(distance),
	m_ParycentricCoord(uvw)
{
}

Intersection::~Intersection(void)
{
}
