#pragma once

#include <vector>

#include "Object.h"

class Mesh :
	public Object
{
public:
	Mesh(unsigned polygon_count, const unsigned* vertices_per_polygon, const Vector3* vertex_buffer, 
		const unsigned* vertex_index_buffer = nullptr, bool is_double_sided = false);

	List(Triangle) Triangles() const;

	unsigned NumTriangles() const;

	~Mesh(void);

protected:
	shared_ptr<IBoundingVolume> ConstructBoundingVolume() const;

	void OnEnableDoubleSided(bool is_double_sided);

	bool OnIntersect(const Ray& ray, Intersection& intersection, void* additional_data) const;

private:
	List(Triangle) m_Triangles;
	vector<Vector3> m_Vertices;
};