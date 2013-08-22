#pragma once

#include "ColorRGBA.h"

class IRenderTarget
{
public:
	virtual void SetPixel(unsigned row, unsigned column, const ColorRGBA& color) = 0;

	virtual ColorRGBA PixelAt(unsigned row, unsigned column) const = 0;

	virtual unsigned Width() const = 0;
	
	virtual unsigned Height() const = 0;

	virtual ~IRenderTarget() = 0 {}
};