#pragma once

#include "Renderer.h"

class RayTracer : public Renderer
{
public:
	RayTracer(void);

	virtual void Render() const;

	~RayTracer(void);

protected:
	virtual ColorRGBA Trace(const Ray& ray, const List(IIntersectTarget)& geometries, const ColorRGBA& background_color = ColorRGBA()) const;

	virtual ColorRGBA Shade(const Ray& ray, const Intersection& intersection) const;
};

