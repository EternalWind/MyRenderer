#include <math.h>

#include "Vector3.h"

Vector3::Vector3(float x, float y, float z)
{
	m_Elements[0] = x;
	m_Elements[1] = y;
	m_Elements[2] = z;
}

Vector3::Vector3(const SphericalCoord& spherical_coordinates)
{
	m_Elements[0] = cos(spherical_coordinates.Phi) * sin(spherical_coordinates.Theta) * spherical_coordinates.Length;
	m_Elements[1] = cos(spherical_coordinates.Theta) * spherical_coordinates.Length;
	m_Elements[2] = sin(spherical_coordinates.Phi) * sin(spherical_coordinates.Theta) * spherical_coordinates.Length;
}

Vector3::Vector3(const Vector<3>& other) :
	Vector<3>(other)
{
}

Vector3 Vector3::CrossProduct(const Vector3& other) const
{
	Vector3 result;

	result.m_Elements[0] = this->m_Elements[1] * other.m_Elements[2] - this->m_Elements[2] * other.m_Elements[1];
	result.m_Elements[1] = this->m_Elements[2] * other.m_Elements[0] - this->m_Elements[0] * other.m_Elements[2];
	result.m_Elements[2] = this->m_Elements[0] * other.m_Elements[1] - this->m_Elements[1] * other.m_Elements[0];

	return result;
}

SphericalCoord Vector3::GetSphericalCoordinates() const
{
	SphericalCoord spherical_coordinates;
	Vector3 normalised_vec = *this;
	
	spherical_coordinates.Length = normalised_vec.Normalise();
	spherical_coordinates.Theta = acos(normalised_vec.m_Elements[1]);
	spherical_coordinates.Phi = atan2f(normalised_vec.m_Elements[2], normalised_vec.m_Elements[0]);
	
	if (spherical_coordinates.Phi < 0.0f)
		spherical_coordinates.Phi += 2 * (float)M_PI;

	return spherical_coordinates;
}

//Vector3::~Vector3(void)
//{
//}
