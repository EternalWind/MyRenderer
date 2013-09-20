#pragma once

#include "Scene.h"

class SimpleScene :
	public Scene
{
public:
	SimpleScene(const ColorRGBA& background_color = ColorRGBA());

	bool Intersect(const Ray& ray, Intersection& intersection, void* additional_data = nullptr) const;
	
	~SimpleScene(void);

protected:
	void OnInitialize();
};

