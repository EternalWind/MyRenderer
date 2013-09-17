#pragma once

#include "IIntersectTarget.h"
#include "Matrix44.h"

class Primitive : public IIntersectTarget
{
public:
	Primitive(const ColorRGBA& color);

	ColorRGBA Color() const;

	void SetColor(const ColorRGBA& color);

	virtual ~Primitive(void) = 0;

protected:
	ColorRGBA m_Color;
	Matrix44 m_W2OTransformation;
	Matrix44 m_O2WTransformation;
};

inline ColorRGBA Primitive::Color() const
{
	return m_Color;
}

inline void Primitive::SetColor(const ColorRGBA& color)
{
	m_Color = color;
}