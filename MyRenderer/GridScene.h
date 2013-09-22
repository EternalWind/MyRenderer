#pragma once

#include "Scene.h"
#include "Grid.h"

class GridScene :
	public Scene
{
public:
	GridScene(const ColorRGBA& background_color = ColorRGBA());

	bool Intersect(const Ray& ray, Intersection& intersection, void* additional_data) const;

	~GridScene(void);

protected:
	void OnInitialize();

private:
	Grid m_Grid;
};

