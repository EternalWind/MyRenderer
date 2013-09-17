#pragma once

#include "Primitive.h"

class Triangle :
	public Primitive
{
public:
	Triangle();

	Triangle(const Vector3* v0, const Vector3* v1, const Vector3* v2, const ColorRGBA& color = ColorRGBA(1.f, 1.f, 1.f), bool is_double_sided = false);

	Triangle(const Triangle& other);

	bool Intersect(const Ray& ray, Intersection& intersection) const;

	bool IsDoubleSided() const;

	void EnableDoubleSided(bool is_double_sided);

	~Triangle(void);

private:
	const Vector3* m_V0;
	const Vector3* m_V1;
	const Vector3* m_V2;

	Vector3 m_Normal;
	Vector3 m_V0V1;
	Vector3 m_V0V2;
	
	float m_D;
	float m_NormalSqLength;

	bool m_IsDoubleSided;
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