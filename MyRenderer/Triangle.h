#pragma once

#include <array>

#include "Primitive.h"

class Triangle :
	public Primitive
{
public:
	Triangle();

	Triangle(const Vector3* v0, const Vector3* v1, const Vector3* v2, const ColorRGBA& color = ColorRGBA(1.f, 1.f, 1.f), bool is_double_sided = false);

	Triangle(const Triangle& other);

	bool Intersect(const Ray& ray, Intersection& intersection, void* additional_data = nullptr) const;

	bool IsDoubleSided() const;

	void EnableDoubleSided(bool is_double_sided);

	const Vector3& Vertex(unsigned i) const;

	const Vector3& MinExtent() const;

	const Vector3& MaxExtent() const;

	~Triangle(void);

private:
	array<const Vector3*, 3> m_V;

	Vector3 m_Normal;
	Vector3 m_V0V1;
	Vector3 m_V0V2;
	Vector3 m_MinExtent;
	Vector3 m_MaxExtent;
	
	float m_D;
	float m_NormalSqLength;

	bool m_IsDoubleSided;

	int m_LastRayId;
};

// Implementation for inline methods.

inline bool Triangle::IsDoubleSided() const
{
	return m_IsDoubleSided;
}

inline void Triangle::EnableDoubleSided(bool is_double_sided)
{
	m_IsDoubleSided = is_double_sided;
}

inline const Vector3& Triangle::Vertex(unsigned i) const
{
#ifdef DEBUG
	if (i > 2)
		throw Exception("Tried to accees the 4th vertex of a triangle which appearantly only has 3!");
#endif
	return *m_V[i];
}

inline const Vector3& Triangle::MinExtent() const
{
	return m_MinExtent;
}

inline const Vector3& Triangle::MaxExtent() const
{
	return m_MaxExtent;
}