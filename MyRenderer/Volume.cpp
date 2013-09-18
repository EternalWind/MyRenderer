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

Volume::Volume(Range<float> extents[m_NumSlabs_s], const ColorRGBA& color) :
	Primitive(color)
{
	++Profiler::numBoundingVolumes;

	size_t size = sizeof(Range<float>) * m_NumSlabs_s;

	if (extents != nullptr)
		memcpy_s(m_Extents, size, extents, size);
}

Volume::Volume(const Volume& other) :
	Primitive(other.m_Color)
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
		intersection.SetDistance(t_far);
	else
		return false;

	intersection.SetIntersectObject((IIntersectTarget*)this);
	intersection.SetTestObject(&ray);

	return true;
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
