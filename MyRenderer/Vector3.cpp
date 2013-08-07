#include <math.h>

#include "Vector3.h"

Vector3::Vector3(float x, float y, float z)
{
	SetX(x);
	SetY(y);
	SetZ(z);
}

Vector3::Vector3(const SphericalCoord& spherical_coordinates)
{
	SetX(cos(spherical_coordinates.Phi) * sin(spherical_coordinates.Theta) * spherical_coordinates.Length);
	SetY(cos(spherical_coordinates.Theta) * spherical_coordinates.Length);
	SetZ(sin(spherical_coordinates.Phi) * sin(spherical_coordinates.Theta) * spherical_coordinates.Length);
}

float Vector3::X() const
{
	return m_Elements[0];
}

float Vector3::Y() const
{
	return m_Elements[1];
}

float Vector3::Z() const
{
	return m_Elements[2];
}

void Vector3::SetX(float x)
{
	m_Elements[0] = x;
}

void Vector3::SetY(float y)
{
	m_Elements[1] = y;
}

void Vector3::SetZ(float z)
{
	m_Elements[2] = z;
}

Vector3 Vector3::CrossProduct(const Vector3& other) const
{
	Vector3 result;

	result.SetX(this->Y() * other.Z() - this->Z() * other.Y());
	result.SetY(this->Z() * other.X() - this->X() * other.Z());
	result.SetZ(this->X() * other.Y() - this->Y() * other.X());

	return result;
}

SphericalCoord Vector3::GetSphericalCoordinates() const
{
	SphericalCoord spherical_coordinates;
	Vector3 normalised_vec = *this;
	
	spherical_coordinates.Length = normalised_vec.Normalise();
	spherical_coordinates.Theta = acos(normalised_vec.Y());
	spherical_coordinates.Phi = atan2f(normalised_vec.Z(), normalised_vec.X());
	
	if (spherical_coordinates.Phi < 0.0f)
		spherical_coordinates.Phi += 2 * (float)M_PI;

	return spherical_coordinates;
}

Vector3::~Vector3(void)
{
}
