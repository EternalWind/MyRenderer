#pragma once

#include <vector>

#include "Object.h"
#include "Triangle.h"

class Mesh :
	public Object
{
public:
	Mesh(unsigned polygon_count, const unsigned* vertices_per_polygon, const Vector3* vertex_buffer, 
		const unsigned* vertex_index_buffer = nullptr, bool is_double_sided = false);

	~Mesh(void);

protected:
	void OnEnableDoubleSided(bool is_double_sided);

	bool OnIntersect(const Ray& ray, Intersection& intersection) const;

private:
	vector<Triangle> m_Triangles;
	vector<Vector3> m_Vertices;
};