#pragma once

#include <memory>

#include "ColorRGBA.h"

class Image
{
public:
	Image(unsigned width, unsigned height);

	Image(const Image& other);

	/**
	  * Construct the image from a file. Only ppm supported.
	  */
	Image(string path);

	Image operator = (const Image& other);

	void SetPixel(unsigned row, unsigned column, const ColorRGBA& color);

	ColorRGBA PixelAt(unsigned row, unsigned column) const;

	unsigned Width() const;

	unsigned Height() const;

	void SaveAsPPM(string path, bool gamma_encoding = false, float gamma = 2.2f) const;

	~Image(void);

private:
	unsigned m_Width;
	unsigned m_Height;
	unique_ptr<ColorRGBA[]> m_Data;
};

// Implementation for inline methods.

inline void Image::SetPixel(unsigned row, unsigned column, const ColorRGBA& color)
{
	if (row >= m_Height)
		throw Exception("The given row index exceeds the height of the image.");
	if (column >= m_Width)
		throw Exception("The given column index exceeds the width of the image.");

	m_Data.get()[row * m_Width + column] = color;
}

inline ColorRGBA Image::PixelAt(unsigned row, unsigned column) const
{
	if (row >= m_Height)
		throw Exception("The given row index exceeds the height of the image.");
	if (column >= m_Width)
		throw Exception("The given column index exceeds the width of the image.");

	return m_Data.get()[row * m_Width + column];
}

inline unsigned Image::Width() const
{
	return m_Width;
}

inline unsigned Image::Height() const
{
	return m_Height;
}