#pragma once

#include "Vector.h"

struct SphericalCoord
{
	SphericalCoord(float theta = 0.f, float phi = 0.f, float length = 1.f) : Theta(theta), Phi(phi), Length(length) {}

	float Theta;
	float Phi;
	float Length;
};

class Vector3 : public Vector<3>
{
public:
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	Vector3(const SphericalCoord& spherical_coordinates);

	Vector3(const Vector<3>& other);

	float X() const;

	float Y() const;

	float Z() const;

	void SetX(float x);

	void SetY(float y);

	void SetZ(float z);

	Vector3 CrossProduct(const Vector3& other) const;

	SphericalCoord GetSphericalCoordinates() const;

	//~Vector3(void);
};

// Implementation for inline methods.

inline float Vector3::X() const
{
	return m_Elements[0];
}

inline float Vector3::Y() const
{
	return m_Elements[1];
}

inline float Vector3::Z() const
{
	return m_Elements[2];
}

inline void Vector3::SetX(float x)
{
	m_Elements[0] = x;
}

inline void Vector3::SetY(float y)
{
	m_Elements[1] = y;
}

inline void Vector3::SetZ(float z)
{
	m_Elements[2] = z;
}