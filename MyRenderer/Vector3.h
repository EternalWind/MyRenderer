#pragma once

#include "Vector.h"

struct SphericalCoord
{
	float Theta;
	float Phi;
	float Length;
};

class Vector3 : public Vector<3>
{
public:
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	Vector3(const SphericalCoord& spherical_coordinates);

	float inline X() const;

	float inline Y() const;

	float inline Z() const;

	void inline SetX(float x);

	void inline SetY(float y);

	void inline SetZ(float z);

	Vector3 CrossProduct(const Vector3& other) const;

	SphericalCoord GetSphericalCoordinates() const;

	~Vector3(void);
};