#include "AABB.h"


AABB::AABB(const Vector3& min_extent, const Vector3& max_extent, const ColorRGBA& color) :
	Shape(color),
	m_MinExtent(min_extent),
	m_MaxExtent(max_extent)
{
}

AABB::~AABB(void)
{
}

shared_ptr<Intersection> AABB::Intersect(const Ray& ray) const
{
	Vector3 origin = ray.Origin();
	Vector3 inversed_dir = ray.InvDirection();

	Range<float> t, t_y, t_z;

	if (inversed_dir.X() >= 0)
	{
		t.Max = (m_MaxExtent.X() - origin.X()) * inversed_dir.X();
		t.Min = (m_MinExtent.X() - origin.X()) * inversed_dir.X();
	}
	else
	{
		t.Min = (m_MaxExtent.X() - origin.X()) * inversed_dir.X();
		t.Max = (m_MinExtent.X() - origin.X()) * inversed_dir.X();
	}

	if (inversed_dir.Y() >= 0)
	{
		t_y.Max = (m_MaxExtent.Y() - origin.Y()) * inversed_dir.Y();
		t_y.Min = (m_MinExtent.Y() - origin.Y()) * inversed_dir.Y();
	}
	else
	{
		t_y.Min = (m_MaxExtent.Y() - origin.Y()) * inversed_dir.Y();
		t_y.Max = (m_MinExtent.Y() - origin.Y()) * inversed_dir.Y();
	}

	if (t.Min > t_y.Max || t_y.Min > t.Max)
		return nullptr;

	if (t.Min < t_y.Min)
		t.Min = t_y.Min;
	if (t.Max > t_y.Max)
		t.Max = t_y.Max;

	if (inversed_dir.Z() >= 0)
	{
		t_z.Max = (m_MaxExtent.Z() - origin.Z()) * inversed_dir.Z();
		t_z.Min = (m_MinExtent.Z() - origin.Z()) * inversed_dir.Z();
	}
	else
	{
		t_z.Min = (m_MaxExtent.Z() - origin.Z()) * inversed_dir.Z();
		t_z.Max = (m_MinExtent.Z() - origin.Z()) * inversed_dir.Z();
	}

	if (t.Min > t_z.Max || t_z.Min > t.Max)
		return nullptr;

	if (t.Min < t_z.Min)
		t.Min = t_z.Min;
	if (t.Max > t_z.Max)
		t.Max = t_z.Max;

	Range<float> range = ray.EffectRange();

	if (Math::Contain(t.Min, range))
	{
		return shared_ptr<Intersection>(new Intersection(ray.Origin() + ray.Direction() * t.Min, this, t.Min));
	}
	else if (Math::Contain(t.Max, range))
	{
		return shared_ptr<Intersection>(new Intersection(ray.Origin() + ray.Direction() * t.Max, this, t.Max));
	}
	else
	{
		return nullptr;
	}
}