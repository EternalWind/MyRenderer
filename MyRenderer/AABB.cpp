#include "AABB.h"


AABB::AABB(const Vector3& min_extent, const Vector3& max_extent) :
	m_MinExtent(min_extent),
	m_MaxExtent(max_extent)
{
}

AABB::~AABB(void)
{
}

bool AABB::Intersect(const Ray& ray) const
{
	Vector3 origin = ray.Origin();
	Vector3 inversed_dir = ray.InvDirection();

	float t_max, t_min, t_y_max, t_y_min, t_z_max, t_z_min;

	if (inversed_dir.X() >= 0)
	{
		t_max = (m_MaxExtent.X() - origin.X()) * inversed_dir.X();
		t_min = (m_MinExtent.X() - origin.X()) * inversed_dir.X();
	}
	else
	{
		t_min = (m_MaxExtent.X() - origin.X()) * inversed_dir.X();
		t_max = (m_MinExtent.X() - origin.X()) * inversed_dir.X();
	}

	if (inversed_dir.Y() >= 0)
	{
		t_y_max = (m_MaxExtent.Y() - origin.Y()) * inversed_dir.Y();
		t_y_min = (m_MinExtent.Y() - origin.Y()) * inversed_dir.Y();
	}
	else
	{
		t_y_min = (m_MaxExtent.Y() - origin.Y()) * inversed_dir.Y();
		t_y_max = (m_MinExtent.Y() - origin.Y()) * inversed_dir.Y();
	}

	if (t_min > t_y_max || t_y_min > t_max)
		return false;

	if (t_min < t_y_min)
		t_min = t_y_min;
	if (t_max > t_y_max)
		t_max = t_y_max;

	if (inversed_dir.Z() >= 0)
	{
		t_z_max = (m_MaxExtent.Z() - origin.Z()) * inversed_dir.Z();
		t_z_min = (m_MinExtent.Z() - origin.Z()) * inversed_dir.Z();
	}
	else
	{
		t_z_min = (m_MaxExtent.Z() - origin.Z()) * inversed_dir.Z();
		t_z_max = (m_MinExtent.Z() - origin.Z()) * inversed_dir.Z();
	}

	if (t_min > t_z_max || t_z_min > t_max)
		return false;

	if (t_min < t_y_min)
		t_min = t_y_min;
	if (t_max > t_y_max)
		t_max = t_y_max;

	return !(t_min > ray.MaxLength() || t_max < ray.MinLength());
}