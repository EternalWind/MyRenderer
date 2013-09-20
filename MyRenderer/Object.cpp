#include "Object.h"


Object::Object(void) :
	m_IsInitialized(false),
	m_IsDoubleSided(false),
	m_BoundingVolume(nullptr)
{
}

void Object::Initialize()
{
	if (!m_IsInitialized)
	{
		m_BoundingVolume = ConstructBoundingVolume();

		m_IsInitialized = true;
	}
}

bool Object::Intersect(const Ray& ray, Intersection& intersection, void* additional_data) const
{
	if (m_BoundingVolume->Intersect(ray, intersection, additional_data))
		return OnIntersect(ray, intersection, additional_data);
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

shared_ptr<IBoundingVolume> Object::BoundingVolume() const
{
	return m_BoundingVolume;
}

Object::~Object(void)
{
}
