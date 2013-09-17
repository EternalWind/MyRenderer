#include "Object.h"


Object::Object(void) :
	m_IsDoubleSided(false),
	m_BoundingVolume(nullptr)
{
}

bool Object::Intersect(const Ray& ray, Intersection& intersection) const
{
	if (m_BoundingVolume->Intersect(ray, intersection))
		return OnIntersect(ray, intersection);
	else
		return false;
}

bool Object::IsDoubleSided() const
{
	return m_IsDoubleSided;
}

void Object::EnableDoubleSided(bool is_double_sided)
{
	if (m_IsDoubleSided != is_double_sided)
	{
		OnEnableDoubleSided(is_double_sided);
		m_IsDoubleSided = is_double_sided;
	}
}

Object::~Object(void)
{
}
