#include "AABB.h"
#include "Profiler.h"

AABB::AABB()
{
	float max = numeric_limits<float>::max();
	float min = -max;

	m_MinExtent.SetX(max);
	m_MinExtent.SetY(max);
	m_MinExtent.SetZ(max);

	m_MaxExtent.SetX(min);
	m_MaxExtent.SetY(min);
	m_MaxExtent.SetZ(min);

	++Profiler::numBoundingVolumes;
}

AABB::AABB(const Vector3& min_extent, const Vector3& max_extent, const ColorRGBA& color) :
	m_MinExtent(min_extent),
	m_MaxExtent(max_extent)
{
	++Profiler::numBoundingVolumes;
}

AABB::AABB(const AABB& other) :
	m_MinExtent(other.m_MinExtent),
	m_MaxExtent(other.m_MaxExtent)
{
	++Profiler::numBoundingVolumes;
}

AABB::~AABB(void)
{
	--Profiler::numBoundingVolumes;
}

bool AABB::Intersect(const Ray& ray, Intersection& intersection, void* additional_data) const
{
	++Profiler::numRayVolumeTestsPerFrame;

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
		return false;

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
		return false;

	if (t.Min < t_z.Min)
		t.Min = t_z.Min;
	if (t.Max > t_z.Max)
		t.Max = t_z.Max;

	Range<float> range = ray.EffectRange();

	if (Math::Contain(t.Min, range))
		intersection.SetDistance(t.Min);
	else if (Math::Contain(t.Max, range))
		intersection.SetDistance(0.f);
	else if (range.Min > t.Min && range.Max < t.Max)
		intersection.SetDistance(0.f);
	else
		return false;

	intersection.SetIntersectObject((IIntersectTarget*)this);
	intersection.SetTestObject(&ray);

	return true;
}

void AABB::ExtendBy(const IBoundingVolume* other)
{
	Vector3 min_extent = other->MinExtent();
	Vector3 max_extent = other->MaxExtent();

	if (m_MinExtent.X() > min_extent.X())
		m_MinExtent.SetX(min_extent.X());
	if (m_MinExtent.Y() > min_extent.Y())
		m_MinExtent.SetY(min_extent.Y());
	if (m_MinExtent.Z() > min_extent.Z())
		m_MinExtent.SetZ(min_extent.Z());

	if (m_MaxExtent.X() < max_extent.X())
		m_MaxExtent.SetX(max_extent.X());
	if (m_MaxExtent.Y() < max_extent.Y())
		m_MaxExtent.SetY(max_extent.Y());
	if (m_MaxExtent.Z() < max_extent.Z())
		m_MaxExtent.SetZ(max_extent.Z());
}