#include "ColorXYZ.h"

ColorXYZ::ColorXYZ(float x, float y, float z)
{
	SetX(x);
	SetY(y);
	SetZ(z);
}

float ColorXYZ::X() const
{
	return m_Elements[0];
}

float ColorXYZ::Y() const
{
	return m_Elements[1];
}

float ColorXYZ::Z() const
{
	return m_Elements[2];
}

void ColorXYZ::SetX(float x)
{
	m_Elements[0] = x;
}

void ColorXYZ::SetY(float y)
{
	m_Elements[1] = y;
}

void ColorXYZ::SetZ(float z)
{
	m_Elements[2] = z;
}

ColorXYZ::~ColorXYZ(void)
{
}
