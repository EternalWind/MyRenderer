#pragma once

#include "Defs.h"
#include "Mesh.h"
#include "BezierSurface.h"

class PolygonGenerator
{
	MAKE_STATIC(PolygonGenerator)

public:
	static shared_ptr<Mesh> Sphere(float radius, unsigned divs, const Vector3& position = Vector3());

	template <size_t rows, size_t columns>
	static shared_ptr<Mesh> Surface(const BezierSurface<rows, columns>& bezier_surface, unsigned divs);
};

// Implementation for template methods

template <size_t rows, size_t columns>
shared_ptr<Mesh> PolygonGenerator::Surface(const BezierSurface<rows, columns>& bezier_surface, unsigned divs)
{
	Vector3* vertices = new Vector3[(divs + 1) * (divs + 1)];
	unsigned* vertices_per_polygon = new unsigned[divs * divs];
	unsigned* indices = new unsigned[divs * divs * 4];

	float u = 0.f;
	float v = 0.f;

	float du = 1 / divs;
	float dv = 1 / divs;

	array < BezierCurve<columns>, rows > curves;

	for (unsigned r = 0; r < rows; ++r)
		curves[r] = bezier_surface.CurveAtRow(r);

	for (unsigned i = 0; i < divs + 1; ++i)
	{
		array<Vector3, rows> cps;

		for (unsigned r = 0; r < rows; ++r)
			cps[r] = curves[r].PointAt(u);

		BezierCurve<rows> curve(cps);

		for (unsigned j = 0; j < divs + 1; ++j)
		{
			vertices[i * (divs + 1) + j] = curve.PointAt(v);
			v += dv;
		}

		u += du;
	}

	for (unsigned i = 0, unsigned k = 0; i < divs; ++i)
		for (unsigned j = 0; j < divs; ++j, ++k)
		{
			vertices_per_polygon[k] = 4;
			indices[k * 4] = i * (divs + 1) + j;
			indices[k * 4 + 1] = (i + 1) * (divs + 1) + j;
			indices[k * 4 + 2] = (i + 1) * (divs + 1) + j + 1;
			indices[k * 4 + 3] = i * (divs + 1) + j + 1;
		}

		auto mesh = shared_ptr<Mesh>(new Mesh(divs * divs, vertices_per_polygon, vertices, indices));

		delete[] vertices;
		delete[] vertices_per_polygon;
		delete[] indices;

		return mesh;
}