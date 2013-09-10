#include "Mesh.h"


Mesh::Mesh(unsigned polygon_count, const unsigned* vertices_per_polygon, const Vector3* vertex_buffer, const unsigned* vertex_index_buffer)
{
	unsigned vertex_count = 0;
	unsigned vertex_index_count = 0;
	unsigned triangle_count = 0;
	unsigned index = 0;

	for (unsigned i = 0; i < polygon_count; ++i)
	{
		if (vertex_index_buffer != nullptr)
			for (unsigned j = 0; j < vertices_per_polygon[i]; ++j)
				if (vertex_count < vertex_index_buffer[vertex_index_count + j])
					vertex_count = vertex_index_buffer[vertex_index_count + j];

		vertex_index_count += vertices_per_polygon[i];
		triangle_count += vertices_per_polygon[i] - 2;
	}

	if (vertex_index_buffer == nullptr)
		vertex_count = vertex_index_count;
	else
		vertex_count += 1;

	m_Triangles.reserve(triangle_count);
	m_Vertices.resize(vertex_count);

	memcpy(m_Vertices.data(), vertex_buffer, vertex_count * sizeof(Vector3));

	for (unsigned i = 0; i < polygon_count; ++i)
	{
		for (unsigned j = 1; j < vertices_per_polygon[i] - 1; ++j)
			if (vertex_index_buffer != nullptr)
			{
				const Vector3* v1_i = m_Vertices.data() + vertex_index_buffer[index];
				const Vector3* v2_i = m_Vertices.data() + vertex_index_buffer[index + j];
				const Vector3* v3_i = m_Vertices.data() + vertex_index_buffer[index + j + 1];

				m_Triangles.push_back(Triangle(v1_i, v2_i, v3_i));
			}
			else
			{
				const Vector3* v1_i = m_Vertices.data() + index;
				const Vector3* v2_i = m_Vertices.data() + index + j;
				const Vector3* v3_i = m_Vertices.data() + index + j + 1;

				m_Triangles.push_back(Triangle(v1_i, v2_i, v3_i));
			}

			index += vertices_per_polygon[i];
	}
}

bool Mesh::Intersect(const Ray& ray, Intersection& intersection) const
{
	float closest_distance = ray.EffectRange().Max;

	for (auto begin = m_Triangles.begin(); begin != m_Triangles.end(); ++begin)
	{
		Intersection hit;

		if (begin->Intersect(ray, hit) && hit.Distance() < closest_distance)
		{
			closest_distance = hit.Distance();
			intersection = hit;
		}
	}

	if (closest_distance < ray.EffectRange().Max)
		return true;
	else
		return false;
}

Mesh::~Mesh(void)
{
}
