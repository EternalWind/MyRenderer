#pragma once

#include "IIntersectTarget.h"

class Shape : public IIntersectTarget
{
public:
	Shape(const ColorRGBA& color);

	ColorRGBA Color() const;

	void SetColor(const ColorRGBA& color);

	virtual ~Shape(void) = 0;

protected:
	ColorRGBA m_Color;
};

inline ColorRGBA Shape::Color() const
{
	return m_Color;
}

inline void Shape::SetColor(const ColorRGBA& color)
{
	m_Color = color;
}