#pragma once
#include "vector.h"

class ColorRGBA : public Vector<4>
{
public:
	ColorRGBA(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f);

	ColorRGBA(const Vector<4>& vec);

	float Red() const;

	float Green() const;

	float Blue() const;

	float Alpha() const;

	void SetRed(float red);

	void SetGreen(float green);

	void SetBlue(float blue);

	void SetAlpha(float alpha);

	ColorRGBA Composite(const ColorRGBA& foreground) const;

	/**
	  *  Remove the foreground from a composited color. Note that only the rgb values can be recovered. Alpha will be lost.
	  */
	ColorRGBA Decomposite(const ColorRGBA& foreground) const;

	ColorRGBA operator + (const ColorRGBA& foreground) const;

	ColorRGBA operator - (const ColorRGBA& foreground) const;

	~ColorRGBA(void);
};

// Implementation for inline methods.

inline float ColorRGBA::Red() const
{
	return m_Elements[0];
}

inline float ColorRGBA::Green() const
{
	return m_Elements[1];
}

inline float ColorRGBA::Blue() const
{
	return m_Elements[2];
}

inline float ColorRGBA::Alpha() const
{
	return m_Elements[3];
}

inline void ColorRGBA::SetRed(float red)
{
	m_Elements[0] = red;
}

inline void ColorRGBA::SetGreen(float green)
{
	m_Elements[1] = green;
}

inline void ColorRGBA::SetBlue(float blue)
{
	m_Elements[2] = blue;
}

inline void ColorRGBA::SetAlpha(float alpha)
{
	m_Elements[3] = alpha;
}