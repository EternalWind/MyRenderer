#include "PolygonGenerator.h"
#include "Exception.h"
#include "teapotdata.h"

shared_ptr<Mesh> PolygonGenerator::Sphere(float radius, unsigned divs, const Vector3& position)
{
	if (radius <= 0.f)
		throw Exception("Cannot generate a sphere with a radius less than or equaling to zero.");
	if (divs < 2)
		throw Exception("Cannot generate a sphere with a number of divisions less than 2.");

	unsigned vertex_num = (divs - 1) * divs + 2;
	unsigned index_num = (6 + 4 * (divs - 2)) * divs;
	unsigned polygon_num = divs * divs;

	float u = 0.f;
	float v = 0.f;
	float du = (float)M_PI / divs;
	float dv = (float)M_PI * 2 / divs;

	Vector3* vertices = new Vector3[vertex_num];
	unsigned* indices = new unsigned[index_num];
	unsigned* vertices_per_polygon = new unsigned[polygon_num];

	unsigned k = 1;

	vertices[0] = Vector3(SphericalCoord(u, v, radius));
	for (unsigned i = 0; i < divs - 1; ++i)
	{
		u += du;
		for (unsigned j = 0; j < divs; ++j, ++k)
		{
			vertices[k] = Vector3(SphericalCoord(u, v, radius));
			v -= dv;
		}
	}
	vertices[k] = Vector3(SphericalCoord((float)M_PI, 0.f, radius));

	unsigned polygon = 0;
	unsigned vid = 0;
	unsigned index = 0;

	for (unsigned i = 0; i < divs; ++i)
	{
		vid = polygon;

		for (unsigned j = 0; j < divs; ++j)
		{
			if (i == 0)
			{
				vertices_per_polygon[polygon] = 3;

				indices[index] = 0;
				indices[index + 1] = 1 + j;
				indices[index + 2] = j == divs - 1 ? 1 : 2 + j;

				index += 3;
			}
			else if (i == divs - 1)
			{
				vertices_per_polygon[polygon] = 3;

				indices[index] = vid - divs + 1 + j;
				indices[index + 1] = vertex_num - 1;
				indices[index + 2] = j == divs - 1 ? vid - divs + 1 : vid - divs + 2 + j;

				index += 3;
			}
			else
			{
				vertices_per_polygon[polygon] = 4;

				indices[index] = vid - divs + 1 + j;
				indices[index + 1] = vid + 1 + j;
				indices[index + 2] = j == divs - 1 ? vid + 1 : vid + 2 + j;
				indices[index + 3] = j == divs - 1 ? vid - divs + 1 : vid - divs + 2 + j;

				index += 4;
			}

			++polygon;
		}
	}

	auto mesh = shared_ptr<Mesh>(new Mesh(polygon_num, vertices_per_polygon, vertices, indices));

	delete[] vertices;
	delete[] indices;
	delete[] vertices_per_polygon;

	return mesh;
}

MeshGroup PolygonGenerator::Teapot(unsigned divs, bool is_order_inversed)
{
	MeshGroup meshes;

	for (unsigned p = 0; p < kTeapotNumPatches; ++p)
	{
		BezierSurface<4, 4> patch;
		unsigned* patch_data = teapotPatches[p];

		for (unsigned i = 0; i < 4; ++i)
			for (unsigned j = 0; j < 4; ++j)
			{
				unsigned index = i * 4 + j;

				patch.SetControlPoint(i, j, Vector3(
					teapotVertices[patch_data[index] - 1][0],
					teapotVertices[patch_data[index] - 1][1],
					teapotVertices[patch_data[index] - 1][2]));
			}

			meshes.push_back(PolygonGenerator::Surface(patch, divs, is_order_inversed));
	}

	return meshes;
}