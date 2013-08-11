#include "ColorRGBA.h"
#include "Math.h"

ColorRGBA::ColorRGBA(float red, float green, float blue, float alpha)
{
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
	SetAlpha(alpha);
}

ColorRGBA::ColorRGBA(const Vector<4>& vec)
	: Vector<4>(vec)
{
}

ColorRGBA ColorRGBA::Composite(const ColorRGBA& foreground) const
{
	ColorRGBA result = *this;

	result = result * (1 - foreground.Alpha()) + foreground * foreground.Alpha();
	result.SetAlpha(1.f);

	return result;
}

ColorRGBA ColorRGBA::Decomposite(const ColorRGBA& foreground) const
{
	ColorRGBA result = *this;

	result = (result - foreground * foreground.Alpha()) / (1 - foreground.Alpha());
	result.SetAlpha(1.f);

	return result;
}

ColorRGBA ColorRGBA::operator + (const ColorRGBA& foreground) const
{
	return this->Composite(foreground);
}

ColorRGBA ColorRGBA::operator - (const ColorRGBA& foreground) const
{
	return this->Decomposite(foreground);
}

ColorRGBA::~ColorRGBA(void)
{
}
