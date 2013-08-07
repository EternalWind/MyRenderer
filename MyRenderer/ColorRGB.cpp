#include "ColorRGB.h"
#include "Math.h"

ColorRGB::ColorRGB(float red, float green, float blue)
{
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
}

float ColorRGB::Red() const
{
	return m_Elements[0];
}

float ColorRGB::Green() const
{
	return m_Elements[1];
}

float ColorRGB::Blue() const
{
	return m_Elements[2];
}

void ColorRGB::SetRed(float red)
{
	m_Elements[0] = Math::Clamp(red, 1.0f, 0.0f);
}

void ColorRGB::SetGreen(float green)
{
	m_Elements[1] = Math::Clamp(green, 1.0f, 0.0f);
}

void ColorRGB::SetBlue(float blue)
{
	m_Elements[2] = Math::Clamp(blue, 1.0f, 0.0f);
}

ColorRGB::~ColorRGB(void)
{
}
