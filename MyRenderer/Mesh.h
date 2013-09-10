#pragma once

#include <vector>

#include "IIntersectTarget.h"
#include "Triangle.h"

class Mesh :
	public IIntersectTarget
{
public:
	Mesh(unsigned polygon_count, const unsigned* vertices_per_polygon, const Vector3* vertex_buffer, const unsigned* vertex_index_buffer = nullptr);

	bool Intersect(const Ray& ray, Intersection& intersection) const;

	~Mesh(void);

private:
	vector<Triangle> m_Triangles;
	vector<Vector3> m_Vertices;
};