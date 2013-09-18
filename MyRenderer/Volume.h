#pragma once

#include "Primitive.h"

using namespace std;

class Volume :
	public Primitive
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

	Volume(Range<float> extents[m_NumSlabs_s], const ColorRGBA& color = ColorRGBA());

	Volume(const Volume& other);

	bool Intersect(const Ray& ray, Intersection& intersection, void* additional_data = nullptr) const;

	static unsigned NumSlabs();

	static const Vector3* PlaneSetNormals();

	~Volume(void);
};

