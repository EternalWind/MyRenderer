#pragma once
#include "vector.h"

class ColorRGB : public Vector<3>
{
public:
	ColorRGB(float red = 0.0f, float green = 0.0f, float blue = 0.0f);

	inline float Red() const;

	inline float Green() const;

	inline float Blue() const;

	inline void SetRed(float red);

	inline void SetGreen(float green);

	inline void SetBlue(float blue);

	~ColorRGB(void);
};

