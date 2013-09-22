#include "Volume.h"
#include "Profiler.h"

const Vector3 Volume::m_PlaneSetNormals_s[Volume::m_NumSlabs_s] = { 
	Vector3(1.f, 0.f, 0.f), 
	Vector3(0.f, 1.f, 0.f), 
	Vector3(0.f, 0.f, 1.f),
	Vector3(sqrtf(3) / 3.f, sqrtf(3) / 3.f, sqrtf(3) / 3.f),
	Vector3(-sqrtf(3) / 3.f, sqrtf(3) / 3.f, sqrtf(3) / 3.f),
	Vector3(-sqrtf(3) / 3.f, -sqrtf(3) / 3.f, sqrtf(3) / 3.f),
	Vector3(sqrtf(3) / 3.f, -sqrtf(3) / 3.f, sqrtf(3) / 3.f) };

Volume::PrecomputedValues::PrecomputedValues(const Ray& ray)
{
	for (unsigned i = 0; i < m_NumSlabs_s; ++i)
	{
		numerators[i] = ray.Origin().DotProduct(m_PlaneSetNormals_s[i]);
		denominators[i] = ray.Direction().DotProduct(m_PlaneSetNormals_s[i]);
	}
}

Volume::Volume(Range<float> extents[m_NumSlabs_s], const ColorRGBA& color)
{
	++Profiler::numBoundingVolumes;

	size_t size = sizeof(Range<float>) * m_NumSlabs_s;

	if (extents != nullptr)
		memcpy_s(m_Extents, size, extents, size);
	else
		for (unsigned i = 0; i < m_NumSlabs_s; ++i)
		{
			m_Extents[i].Max = -numeric_limits<float>::max();
			m_Extents[i].Min = numeric_limits<float>::max();
		}
}

Volume::Volume(const Volume& other)
{
	++Profiler::numBoundingVolumes;

	size_t size = sizeof(Range<float>) * m_NumSlabs_s;
	memcpy_s(m_Extents, size, other.m_Extents, size);
}

bool Volume::Intersect(const Ray& ray, Intersection& intersection, void* additional_data) const
{
	++Profiler::numRayVolumeTestsPerFrame;

	float t_near = -numeric_limits<float>::max();
	float t_far = -t_near;
	PrecomputedValues* values = (PrecomputedValues*)additional_data;

	for (unsigned i = 0; i < m_NumSlabs_s; ++i)
	{
		float numerator = values != nullptr ? values->numerators[i] : ray.Origin().DotProduct(m_PlaneSetNormals_s[i]);
		float denominator = values != nullptr ? values->denominators[i] : ray.Direction().DotProduct(m_PlaneSetNormals_s[i]);
		float t0 = (m_Extents[i].Min - numerator) / denominator;
		float t1 = (m_Extents[i].Max - numerator) / denominator;

		if (denominator < 0.f)
			swap(t0, t1);

		if (t0 > t_near)
			t_near = t0;
		if (t1 < t_far)
			t_far = t1;

		if (t_far < t_near)
			return false;
	}

	if (Math::Contain(t_near, ray.EffectRange()))
		intersection.SetDistance(t_near);
	else if (Math::Contain(t_far, ray.EffectRange()))
		intersection.SetDistance(0.f);
	else if (ray.EffectRange().Max < t_far && ray.EffectRange().Min > t_near)
		intersection.SetDistance(0.f);
	else
		return false;

	intersection.SetIntersectObject((IIntersectTarget*)this);
	intersection.SetTestObject(&ray);

	return true;
}

void Volume::ExtendBy(const IBoundingVolume* other)
{
	const Volume* vol = dynamic_cast<const Volume*>(other);

	if (vol != nullptr)
	{
		for (unsigned i = 0; i < m_NumSlabs_s; ++i)
		{
			if (vol->m_Extents[i].Max > m_Extents[i].Max)
				m_Extents[i].Max = vol->m_Extents[i].Max;
			if (vol->m_Extents[i].Min < m_Extents[i].Min)
				m_Extents[i].Min = vol->m_Extents[i].Min;
		}
	}
	else
	{
		Vector3 min_extent = other->MinExtent();
		Vector3 max_extent = other->MaxExtent();

		for (unsigned i = 0; i < 3; ++i)
		{
			if (m_Extents[i].Min > min_extent[i])
				m_Extents[i].Min = min_extent[i];
			if (m_Extents[i].Max > max_extent[i])
				m_Extents[i].Max = max_extent[i];
		}
	}
}

Vector3 Volume::MinExtent() const
{
	return Vector3(m_Extents[0].Min, m_Extents[1].Min, m_Extents[2].Min);
}

Vector3 Volume::MaxExtent() const
{
	return Vector3(m_Extents[0].Max, m_Extents[1].Max, m_Extents[2].Max);
}

unsigned Volume::NumSlabs()
{
	return m_NumSlabs_s;
}

const Vector3* Volume::PlaneSetNormals()
{
	return m_PlaneSetNormals_s;
}

Volume::~Volume(void)
{
	--Profiler::numBoundingVolumes;
}
