#include "Mesh.h"
#include "AABB.h"

Mesh::Mesh(unsigned polygon_count, const unsigned* vertices_per_polygon, const Vector3* vertex_buffer, 
		   const unsigned* vertex_index_buffer, bool is_double_sided)
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
		{
			Vector3* v1_i = nullptr;
			Vector3* v2_i = nullptr;
			Vector3* v3_i = nullptr;

			if (vertex_index_buffer != nullptr)
			{
				v1_i = m_Vertices.data() + vertex_index_buffer[index];
				v2_i = m_Vertices.data() + vertex_index_buffer[index + j];
				v3_i = m_Vertices.data() + vertex_index_buffer[index + j + 1];
			}
			else
			{
				v1_i = m_Vertices.data() + index;
				v2_i = m_Vertices.data() + index + j;
				v3_i = m_Vertices.data() + index + j + 1;
			}

			m_Triangles.push_back(Triangle(v1_i, v2_i, v3_i, ColorRGBA(1.f, 1.f, 1.f), is_double_sided));
		}
		index += vertices_per_polygon[i];
	}

	float max = numeric_limits<float>::max();
	float min = -numeric_limits<float>::max();

	Vector3 min_ext(max, max, max);
	Vector3 max_ext(min, min, min);

	for (auto iter = m_Vertices.begin(); iter != m_Vertices.end(); ++iter)
	{
		if (iter->X() > max_ext.X())
			max_ext.SetX(iter->X());
		if (iter->Y() > max_ext.Y())
			max_ext.SetY(iter->Y());
		if (iter->Z() > max_ext.Z())
			max_ext.SetZ(iter->Z());

		if (iter->X() < min_ext.X())
			min_ext.SetX(iter->X());
		if (iter->Y() < min_ext.Y())
			min_ext.SetY(iter->Y());
		if (iter->Z() < min_ext.Z())
			min_ext.SetZ(iter->Z());
	}

	if (min_ext.X() != max && max_ext.X() != min)
		m_BoundingVolume.reset(new AABB(min_ext, max_ext));
}

void Mesh::OnEnableDoubleSided(bool is_double_sided)
{
	for (auto iter = m_Triangles.begin(); iter != m_Triangles.end(); ++iter)
		iter->EnableDoubleSided(is_double_sided);
}

bool Mesh::OnIntersect(const Ray& ray, Intersection& intersection) const
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
