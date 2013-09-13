#pragma once

#include "Defs.h"
#include "Mesh.h"
#include "BezierSurface.h"

typedef vector < shared_ptr<Mesh> > MeshGroup;

class PolygonGenerator
{
	MAKE_STATIC(PolygonGenerator)

public:
	static shared_ptr<Mesh> Sphere(float radius, unsigned divs, const Vector3& position = Vector3());

	/**
	  * Generates a surface based on a bezier surface.
	  * @param bezier_surface The beizer surface.
	  * @param divs The number of divisions for the generated surface.
	  * @param is_order_inversed Whether the given bezier surface's control points' order is inversed (From right to left) or not.
	  * @returns A generated surface of course!
	  */
	template <size_t rows, size_t columns>
	static shared_ptr<Mesh> Surface(const BezierSurface<rows, columns>& bezier_surface, unsigned divs, bool is_order_inversed = false);

	static MeshGroup Teapot(unsigned divs, bool is_order_inversed = false);
};

// Implementation for template methods

template <size_t rows, size_t columns>
shared_ptr<Mesh> PolygonGenerator::Surface(const BezierSurface<rows, columns>& bezier_surface, unsigned divs, bool is_order_inversed)
{
	Vector3* vertices = new Vector3[(divs + 1) * (divs + 1)];
	unsigned* vertices_per_polygon = new unsigned[divs * divs];
	unsigned* indices = new unsigned[divs * divs * 4];

	float u = 0.f;
	float v = 0.f;

	float du = 1.0f / divs;
	float dv = 1.0f / divs;

	vector < shared_ptr<ICurve> > curves;
	Vector3* cps;
	unsigned curve_num = 0;

	if (is_order_inversed)
	{
		curves.resize(rows);
		curve_num = rows;

		for (unsigned r = 0; r < rows; ++r)
			curves[r].reset(new BezierCurve<columns>(bezier_surface.CurveAtRow(r)));
	}
	else
	{
		curves.resize(columns);
		curve_num = columns;

		for (unsigned r = 0; r < columns; ++r)
			curves[r].reset(new BezierCurve<rows>(bezier_surface.CurveAtColumn(r)));
	}

	cps = new Vector3[curve_num];

	for (unsigned i = 0; i < divs + 1; ++i)
	{
		for (unsigned r = 0; r < curve_num; ++r)
			cps[r] = curves[r]->PointAt(u);

		ICurve* curve = nullptr;

		if (is_order_inversed)
			curve = new BezierCurve<rows>(cps);
		else
			curve = new BezierCurve<columns>(cps);

		v = 0.f;
		for (unsigned j = 0; j < divs + 1; ++j)
		{
			unsigned index = i * (divs + 1) + j;
			vertices[index] = curve->PointAt(v);
			v += dv;
		}

		u += du;

		delete curve;
	}

	unsigned k = 0;

	for (unsigned i = 0; i < divs; ++i)
		for (unsigned j = 0; j < divs; ++j, ++k)
		{
			vertices_per_polygon[k] = 4;
			indices[k * 4] = i * (divs + 1) + j;
			indices[k * 4 + 1] = (i + 1) * (divs + 1) + j;
			indices[k * 4 + 2] = (i + 1) * (divs + 1) + j + 1;
			indices[k * 4 + 3] = i * (divs + 1) + j + 1;
		}

		auto mesh = shared_ptr<Mesh>(new Mesh(divs * divs, vertices_per_polygon, vertices, indices));

		delete[] vertices_per_polygon;
		delete[] vertices;
		delete[] indices;
		delete[] cps;

		return mesh;
}