#include "GridScene.h"


GridScene::GridScene(const ColorRGBA& background_color) :
	Scene(background_color)
{
}

bool GridScene::Intersect(const Ray& ray, Intersection& intersection, void* additional_data) const
{
	Intersection hit;
	auto bouding_box = m_Grid.BoundingBox();

	if (!bouding_box->Intersect(ray, hit, additional_data))
		return false;

	Vector3 ray_direction = ray.Direction();
	Vector3 inv_ray_direction = ray.InvDirection();
	Vector3 ray_orig_grid = ray.Origin() + ray_direction * hit.Distance() - bouding_box->MinExtent();
	Vector3 delta_t;
	Vector3 next_t;
	int ci_steps[3];
	int indices[3];
	int exit[3];
	const unsigned* grid_resolution = m_Grid.Resolution();
	Vector3 cell_size = m_Grid.CellSize();

	for (unsigned i = 0; i < 3; ++i)
	{
		indices[i] = int(ray_orig_grid[i] / cell_size[i]);

		if (ray_direction[i] > 0.f)
		{
			delta_t[i] = cell_size[i] / ray_direction[i];
			next_t[i] = ((indices[i] + 1) * cell_size[i] - ray_orig_grid[i]) * inv_ray_direction[i];
			ci_steps[i] = 1;
			exit[i] = grid_resolution[i];
		}
		else
		{
			delta_t[i] = -cell_size[i] / ray_direction[i];
			next_t[i] = (indices[i] * cell_size[i] - ray_orig_grid[i]) * inv_ray_direction[i];
			ci_steps[i] = -1;
			exit[i] = -1;
		}
	}

	float closest_distance = numeric_limits<float>::max();
	static unsigned axies[8] = { 2, 0, 1, 1, 2, 0, 0, 0 };

	while (true)
	{
		const Grid::Cell& cell = m_Grid.CellAt(indices[0], indices[1], indices[2]);

		for (auto iter = cell.triangles.begin(); iter != cell.triangles.end(); ++iter)
		{
			if ((*iter)->Intersect(ray, hit, additional_data) && hit.Distance() < closest_distance)
			{
				intersection = hit;
				closest_distance = hit.Distance();
			}
		}

		unsigned k = ((next_t[0] < next_t[1]) << 2) | ((next_t[1] < next_t[2]) << 1) | (next_t[0] < next_t[2]);

		if (next_t[axies[k]] > closest_distance)
			break;

		float t = next_t[axies[k]] += delta_t[axies[k]];
		indices[axies[k]] += ci_steps[axies[k]];

		if (t > ray.EffectRange().Max || exit[axies[k]] == indices[axies[k]])
			break;
	}

	if (closest_distance != numeric_limits<float>::max())
		return true;
	else
		return false;
}

GridScene::~GridScene(void)
{
}

void GridScene::OnInitialize()
{
	m_Grid.Initialize(m_Geometries);
}