#include "Grid.h"


Grid::Grid(float resolution_parameter, unsigned max_resolution) :
	m_BoundingBox(new AABB()),
	m_ResolutionParameter(resolution_parameter),
	m_MaxResolution(max_resolution)
{
}

void Grid::Initialize(const List(Object)& objects)
{
	unsigned total_triangle_number = 0;

	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		auto object = *iter;

		m_BoundingBox->ExtendBy(object->BoundingVolume().get());
		total_triangle_number += object->NumTriangles();
	}

	Vector3 grid_size = m_BoundingBox->MaxExtent() - m_BoundingBox->MinExtent();
	float inv_grid_vol = 1 / (grid_size.X() * grid_size.Y() * grid_size.Z());
	float exp = 1.f / 3.f;
	float res_factor = powf(m_ResolutionParameter * total_triangle_number * inv_grid_vol, exp);
	unsigned total_cell_num = 1;

	for (unsigned i = 0; i < 3; ++i)
	{
		m_Resolution[i] = Math::Clamp(unsigned(grid_size[i] * res_factor), m_MaxResolution, unsigned(1));
		m_CellSize[i] = grid_size[i] / m_Resolution[i];
		total_cell_num *= m_Resolution[i];
	}

	m_Cells.resize(total_cell_num);

	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		Insert(*iter);
}

void Grid::Insert(shared_ptr<Object> object)
{
	auto triangles = object->Triangles();

	static const float max = numeric_limits<float>::max();
	static const float min = -max;

	Vector3 grid_orig = m_BoundingBox->MinExtent();

	for (auto iter = triangles.begin(); iter != triangles.end(); ++iter)
	{
		Vector3 min_extent(max, max, max);
		Vector3 max_extent(min, min, min);

		for (unsigned i = 0; i < 3; ++i)
		{
			const Vector3& vertex = (*iter)->Vertex(i);

			for (unsigned j = 0; j < 3; ++j)
			{
				if (min_extent[j] > vertex[j])
					min_extent[j] = vertex[j];
				if (max_extent[j] < vertex[j])
					max_extent[j] = vertex[j];
			}
		}

		unsigned min_cell_indices[3];
		unsigned max_cell_indices[3];

		for (unsigned i = 0; i < 3; ++i)
		{
			min_cell_indices[i] = Math::Clamp(unsigned((min_extent[i] - grid_orig[i]) / m_CellSize[i]), m_Resolution[i] - 1, unsigned(0));
			max_cell_indices[i] = Math::Clamp(unsigned((max_extent[i] - grid_orig[i]) / m_CellSize[i]), m_Resolution[i] - 1, unsigned(0));
		}

		shared_ptr<Triangle> triangle = *iter;

		for (unsigned z = min_cell_indices[2]; z <= max_cell_indices[2]; ++z)
			for (unsigned y = min_cell_indices[1]; y <= max_cell_indices[1]; ++y)
				for (unsigned x = min_cell_indices[0]; x <= max_cell_indices[0]; ++x)
					_CellAt(x, y, z).triangles.push_back(triangle);
	}
}

Grid::~Grid(void)
{
}
