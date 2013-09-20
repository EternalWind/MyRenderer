#include "SimpleScene.h"
#include "Volume.h"

SimpleScene::SimpleScene(const ColorRGBA& background_color) :
	Scene(background_color)
{
}

void SimpleScene::OnInitialize() {}

bool SimpleScene::Intersect(const Ray& ray, Intersection& intersection, void* additional_data) const
{
	float cloest_distance = ray.EffectRange().Max;
	Volume::PrecomputedValues values(ray);

	for (auto iter_g = m_Geometries.begin(); iter_g != m_Geometries.end(); ++iter_g)
	{
		auto geometry = *iter_g;
		Intersection hit;

		if (geometry->Intersect(ray, hit, &values) && hit.Distance() < cloest_distance)
		{
			intersection = hit;
			cloest_distance = hit.Distance();
		}
	}

	if (cloest_distance != ray.EffectRange().Max)
		return true;
	else
		return false;
}

SimpleScene::~SimpleScene(void)
{
}
