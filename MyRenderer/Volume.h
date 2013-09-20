#pragma once

#include "IBoundingVolume.h"

using namespace std;

class Volume :
	public IBoundingVolume
{
private:
	static const unsigned m_NumSlabs_s = 7;
	static const Vector3 m_PlaneSetNormals_s[m_NumSlabs_s];

	Range<float> m_Extents[m_NumSlabs_s];

public:
	struct PrecomputedValues
	{
		PrecomputedValues(const Ray& ray);

		float numerators[m_NumSlabs_s];
		float denominators[m_NumSlabs_s];
	};

	Volume(Range<float> extents[m_NumSlabs_s] = nullptr, const ColorRGBA& color = ColorRGBA());

	Volume(const Volume& other);

	bool Intersect(const Ray& ray, Intersection& intersection, void* additional_data = nullptr) const;

	void ExtendBy(const IBoundingVolume* other);

	Vector3 MinExtent() const;

	Vector3 MaxExtent() const;

	static unsigned NumSlabs();

	static const Vector3* PlaneSetNormals();

	~Volume(void);
};

