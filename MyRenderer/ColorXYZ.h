#pragma once

#include "vector.h"
#include "SpectralData.h"

class ColorXYZ :
	public Vector<3>
{
public:
	ColorXYZ(float x = .0f, float y = .0f, float z = .0f);

	ColorXYZ(const SpectralData& spectral_data);

	float X() const;

	float Y() const;

	float Z() const;

	void SetX(float x);

	void SetY(float y);

	void SetZ(float z);

	~ColorXYZ(void);
};